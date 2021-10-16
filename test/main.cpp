#include <gtest/gtest.h>

#include "argparse.hpp"

class ArgumentParserTest : public ::testing::Test {
protected:
    ArgumentParser _parser;
};

TEST_F(ArgumentParserTest, Test) {
    _parser.AddArgument<float>("testArg");

    char array[3][50] = {{0}};
    strcpy(array[0], "main");
    strcpy(array[1], "testArg");
    strcpy(array[2], "1.234");

    char* argv[] = {array[0], array[1], array[2]};
    int argc = sizeof(argv) / sizeof(argv[0]);

    try {
        auto args = _parser.ParseArguments(argc, argv);
        ASSERT_FLOAT_EQ(args.GetArg<float>("testArg"), 1.234f);
    } catch (const std::exception& e) {
        ASSERT_TRUE(false) << "Unexpected error - " << e.what();
    }
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
