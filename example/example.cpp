#include <chrono>
#include <iostream>

#include "argparse.hpp"

int main(int argc, char* argv[]) {
    auto t0 = std::chrono::high_resolution_clock::now();

    try {
        ArgumentParser parser;
        parser.AddArgument<float>("test");

        auto args = parser.ParseArguments(argc, argv);

        std::cout << args.GetArg<float>("test") << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to process command line arguments: "
              << std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0)
                     .count()
              << "us" << std::endl;

    return 0;
}