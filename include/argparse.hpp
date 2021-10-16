#include <algorithm>
#include <exception>
#include <optional>
#include <string>
#include <unordered_map>

enum class ArgumentType { Boolean, Integer, Float, Double, String, Unknown };

class ArgumentParserError : public std::runtime_error {
public:
    ArgumentParserError(const std::string& msg) : std::runtime_error(msg) {}
};

class ArgumentValueMap {
public:
    template <typename T>
    void CreateArg(const std::string& name,
                   const std::optional<T>& default_value) {
        static_assert(
            std::is_same<T, bool>::value || std::is_same<T, int>::value ||
                std::is_same<T, float>::value ||
                std::is_same<T, double>::value ||
                std::is_same<T, std::string>::value,
            "Only [bool|int|float|double|string] arguments are supported");
    };

    template <typename T>
    T GetArg(const std::string& name) {
        static_assert(
            std::is_same<T, bool>::value || std::is_same<T, int>::value ||
                std::is_same<T, float>::value ||
                std::is_same<T, double>::value ||
                std::is_same<T, std::string>::value,
            "Only [bool|int|float|double|string] arguments are supported");
    }

    template <typename T>
    void SetArg(const std::string& name, const T& value) {
        static_assert(
            std::is_same<T, bool>::value || std::is_same<T, int>::value ||
                std::is_same<T, float>::value ||
                std::is_same<T, double>::value ||
                std::is_same<T, std::string>::value,
            "Only [bool|int|float|double|string] arguments are supported");
    };

    ArgumentType GetArgType(const std::string& name) const {
        return Contains(name) ? _name_type_map.at(name) : ArgumentType::Unknown;
    }

private:
    bool Contains(const std::string& name) const {
        return _name_type_map.find(name) != _name_type_map.end();
    }

    inline void CheckForDuplicateArgument(const std::string& name) {
        if (const auto it = _name_type_map.find(name);
            it != _name_type_map.end()) {
            throw ArgumentParserError(
                "Duplicate name: " + name +
                " is already used for argument of type " +
                std::to_string(static_cast<int>(it->second)));
        }
    }

    std::unordered_map<std::string, ArgumentType> _name_type_map;
    std::unordered_map<std::string, std::optional<bool>> _bool_args;
    std::unordered_map<std::string, std::optional<int>> _int_args;
    std::unordered_map<std::string, std::optional<float>> _float_args;
    std::unordered_map<std::string, std::optional<double>> _double_args;
    std::unordered_map<std::string, std::optional<std::string>> _string_args;
};

template <>
void ArgumentValueMap::CreateArg<bool>(
    const std::string& name, const std::optional<bool>& default_value) {
    CheckForDuplicateArgument(name);
    _name_type_map.emplace(name, ArgumentType::Boolean);
    _bool_args.emplace(name, default_value);
}

template <>
void ArgumentValueMap::CreateArg<int>(const std::string& name,
                                      const std::optional<int>& default_value) {
    CheckForDuplicateArgument(name);
    _name_type_map.emplace(name, ArgumentType::Integer);
    _int_args.emplace(name, default_value);
}

template <>
void ArgumentValueMap::CreateArg<float>(
    const std::string& name, const std::optional<float>& default_value) {
    CheckForDuplicateArgument(name);
    _name_type_map.emplace(name, ArgumentType::Float);
    _float_args.emplace(name, default_value);
}

template <>
void ArgumentValueMap::CreateArg<double>(
    const std::string& name, const std::optional<double>& default_value) {
    CheckForDuplicateArgument(name);
    _name_type_map.emplace(name, ArgumentType::Double);
    _double_args.emplace(name, default_value);
}

template <>
void ArgumentValueMap::CreateArg<std::string>(
    const std::string& name, const std::optional<std::string>& default_value) {
    CheckForDuplicateArgument(name);
    _name_type_map.emplace(name, ArgumentType::String);
    _string_args.emplace(name, default_value);
}

template <>
void ArgumentValueMap::SetArg<bool>(const std::string& name,
                                    const bool& value) {
    _bool_args[name].emplace(value);
}

template <>
void ArgumentValueMap::SetArg<int>(const std::string& name, const int& value) {
    _int_args[name].emplace(value);
}

template <>
void ArgumentValueMap::SetArg<float>(const std::string& name,
                                     const float& value) {
    _float_args[name].emplace(value);
}

template <>
void ArgumentValueMap::SetArg<double>(const std::string& name,
                                      const double& value) {
    _double_args[name].emplace(value);
}

template <>
void ArgumentValueMap::SetArg<std::string>(const std::string& name,
                                           const std::string& value) {
    _string_args[name].emplace(value);
}

template <>
bool ArgumentValueMap::GetArg<bool>(const std::string& name) {
    if (const auto it = _name_type_map.find(name); it != _name_type_map.end()) {
        if (it->second != ArgumentType::Boolean) {
            throw ArgumentParserError(
                "Attempting to get boolean value from type " +
                std::to_string(static_cast<int>(it->second)));
        }
    }

    if (!_bool_args[name].has_value()) {
        throw ArgumentParserError("No value provided for argument: " + name);
    }

    return _bool_args[name].value();
}

template <>
int ArgumentValueMap::GetArg<int>(const std::string& name) {
    if (const auto it = _name_type_map.find(name); it != _name_type_map.end()) {
        if (it->second != ArgumentType::Integer) {
            throw ArgumentParserError(
                "Attempting to get integer value from type " +
                std::to_string(static_cast<int>(it->second)));
        }
    }

    if (!_int_args[name].has_value()) {
        throw ArgumentParserError("No value provided for argument: " + name);
    }

    return _int_args[name].value();
}

template <>
float ArgumentValueMap::GetArg<float>(const std::string& name) {
    if (const auto it = _name_type_map.find(name); it != _name_type_map.end()) {
        if (it->second != ArgumentType::Float) {
            throw ArgumentParserError(
                "Attempting to get float value from type " +
                std::to_string(static_cast<int>(it->second)));
        }
    }

    if (!_float_args[name].has_value()) {
        throw ArgumentParserError("No value provided for argument: " + name);
    }

    return _float_args[name].value();
}

template <>
double ArgumentValueMap::GetArg<double>(const std::string& name) {
    if (const auto it = _name_type_map.find(name); it != _name_type_map.end()) {
        if (it->second != ArgumentType::Double) {
            throw ArgumentParserError(
                "Attempting to get double value from type " +
                std::to_string(static_cast<int>(it->second)));
        }
    }

    if (!_double_args[name].has_value()) {
        throw ArgumentParserError("No value provided for argument: " + name);
    }

    return _double_args[name].value();
}

template <>
std::string ArgumentValueMap::GetArg<std::string>(const std::string& name) {
    if (const auto it = _name_type_map.find(name); it != _name_type_map.end()) {
        if (it->second != ArgumentType::String) {
            throw ArgumentParserError(
                "Attempting to get string value from type " +
                std::to_string(static_cast<int>(it->second)));
        }
    }

    if (!_string_args[name].has_value()) {
        throw ArgumentParserError("No value provided for argument: " + name);
    }
    
    return _string_args[name].value();
}

class ArgumentParser {
public:
    ArgumentParser() {}
    virtual ~ArgumentParser() {}

    template <typename T>
    void AddArgument(const std::string& name) {
        _argument_value_map.CreateArg<T>(name, std::optional<T>());
    };

    template <typename T>
    void AddArgument(const std::string& name, const T& default_value) {
        _argument_value_map.CreateArg<T>(name, default_value);
    };

    ArgumentValueMap ParseArguments(const int argc, char* argv[]) {
        int ind = 1;
        while (ind < argc) {
            std::string key = argv[ind];
            if (ind + 1 < argc) {
                std::string value = argv[ind + 1];
                switch (_argument_value_map.GetArgType(key)) {
                    case ArgumentType::Boolean:
                        try {
                            auto val = value;
                            std::transform(
                                val.begin(), val.end(), val.begin(),
                                [](const char& c) { return std::tolower(c); });
                            if (value == "true") {
                                _argument_value_map.SetArg<bool>(key, true);
                            } else if (value == "false") {
                                _argument_value_map.SetArg<bool>(key, false);
                            } else {
                                throw ArgumentParserError(
                                    "Unable to parse boolean argument: " + key +
                                    " - " + value);
                            }
                        } catch (const std::exception& e) {
                            throw ArgumentParserError(
                                "Unable to parse boolean argument: " + key +
                                " - " + value);
                        }
                        break;
                    case ArgumentType::Integer:
                        try {
                            auto val = std::stoi(value);
                            _argument_value_map.SetArg<int>(key, val);
                        } catch (const std::exception& e) {
                            throw ArgumentParserError(
                                "Unable to parse integer argument: " + key +
                                " - " + value);
                        }
                        break;
                    case ArgumentType::Float:
                        try {
                            auto val = std::stof(value);
                            _argument_value_map.SetArg<float>(key, val);
                        } catch (const std::exception& e) {
                            throw ArgumentParserError(
                                "Unable to parse float argument: " + key +
                                " - " + value);
                        }
                        break;
                    case ArgumentType::Double:
                        try {
                            auto val = std::stod(value);
                            _argument_value_map.SetArg<double>(key, val);
                        } catch (const std::exception& e) {
                            throw ArgumentParserError(
                                "Unable to parse double argument: " + key +
                                " - " + value);
                        }
                        break;
                    case ArgumentType::String:
                        _argument_value_map.SetArg<std::string>(key, value);
                        break;
                    default:
                        break;
                }
                ++ind;
            }
            ++ind;
        }

        return _argument_value_map;
    }

private:
    ArgumentValueMap _argument_value_map;
};
