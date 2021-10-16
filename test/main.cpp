#include "argparse.hpp"
#include <gtest/gtest.h>

class ArgumentParserTest : public ::testing::Test {
private:
    ArgumentParser _parser;
};

TEST_F(ArgumentParserTest, Test) {

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
