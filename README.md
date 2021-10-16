# argparse-cpp

A C++17 header-only command line argument parser for C++.

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

### Example app

See [example](example) for an example executable. Build it with [build_example.sh](build_example.sh).

## Development

### Tests

- Install googletest (tested with v1.11.0)
- Set GTEST_PATH variable in [third_party.txt](third_party.txt)

## To-Do

- [ ] Positional arguments
- [ ] Arguments as flags
- [ ] Shorthand keyword arguments
- [ ] '--' prefix to denote positional arguments
- [ ] [Github actions + googletest](https://github.com/bastianhjaeger/github_actions_gtest_example)
- [ ] Documentation (doxygen)
