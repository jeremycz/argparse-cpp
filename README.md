# argparse-cpp

A header-only command line argument parser for C++.

## Requirements

- C++17

## Usage

Instantiate an instance of the parser.

```cpp
ArgumentParser parser;
```

Add keyword arguments.

```cpp
parser.AddArgument<float>("name");
```

Parse command line arguments.

```cpp
ArgumentValueMap args = parser.ParseArguments(argc, argv);
```

Retrieve argument values.

```cpp
float float_value = args.GetArg<float>("name");
```
