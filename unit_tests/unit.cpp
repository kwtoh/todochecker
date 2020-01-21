#define CATCH_CONFIG_MAIN 
#include <filesystem>
#include "catch.hpp"
#include "../src/argparser.hpp"
#include "../src/engine.h"

namespace fs = std::filesystem;

// Argument Parser Tests
TEST_CASE("ArgParser Simple Test", "[argparser]")
{
    // Test Empty ArgParser
    ArgParse::ArgParser parser;
    REQUIRE(parser.parseArgs(0, nullptr) == false);

    ArgParse::ArgParserConfigs configs;
    configs.push_back(
        ArgParse::ArgParserConfigType(
            "-b", "-bool", false, 
            "Boolean Test", 
            [](ArgParse::ArgParserValues value, const char* argv)
            {
                assert(argv == nullptr);
                value.m_boolValue = true; 
                return value;
            }));
    configs.push_back(
        ArgParse::ArgParserConfigType(
            "-i", "-int", true, 
            "Integer Test", 
            [](ArgParse::ArgParserValues value, const char* argv)
            {
                value.m_intValue = std::atoi(argv); 
                return value;
            }));

    // Test that parser has taken the configs
    parser.loadConfig(configs);
    REQUIRE(configs.size() == 0);

    //Test that parser map is empty
    REQUIRE(parser.contains("-t") == false);

    // Test that no arguments work
    const char * argvNoParams[1] = {"sample"};
    REQUIRE(parser.parseArgs(1, argvNoParams) == true);

    // Test that argument exists
    const char * argvSingleParam[2] = {"sample", "-b"};
    REQUIRE(parser.parseArgs(2, argvSingleParam) == true);

    // Test that long form argument exists
    const char * argvSingleParamUpper[2] = {"sample", "-bool"};
    REQUIRE(parser.parseArgs(2, argvSingleParamUpper) == true);

    // Test that valued arguement without value is false
    const char * argvSingleParamIntFalse[2] = {"sample", "-i"};
    REQUIRE(parser.parseArgs(2, argvSingleParamIntFalse) == false);

    // Test that valued argument with value 
    const char * argvSingleParamIntTrue[3] = {"sample", "-int", "2"};
    REQUIRE(parser.parseArgs(3, argvSingleParamIntTrue) == true);

    // Test Help Text
    std::string help;
    parser.getHelp(help);
    REQUIRE(help == "Help Text\n-b\t\t-bool\t\tBoolean Test\n-i\t\t-int\t\tInteger Test\n");

    // Test contains function
    REQUIRE(parser.contains("-i") == true);
    REQUIRE(parser.contains("-b") == true);
    REQUIRE(parser.contains("-int") == false);

    // Test ArgParserValue
    ArgParse::ArgParserValues value = parser.getValue("-i");
    REQUIRE(value.m_intValue == 2);

    // Test Get Value function
    value = parser.getValue("-b");
    REQUIRE(value.m_boolValue == true);
}

//  Engine Test Simple
TEST_CASE("Engine Test Simple", "[engine]")
{
    Core::Engine testEngine(false, false);
    
    std::vector<std::string> found;

    std::string testDir = "/test_files/single";
    std::string currDir = fs::current_path();

    std::string testPath = currDir + testDir;
    std::string testTerm = "TODO";
    testEngine.execute(found, testPath, testTerm);

    REQUIRE(found.size() == 1);
    REQUIRE(found[0] == currDir + testDir + "/single.txt");
}

// Engine Test Lower Case 
TEST_CASE("Engine Test Lower Case", "[engine]")
{
    Core::Engine testEngine(true, false);
    
    std::vector<std::string> found;

    std::string testDir = "/test_files/single";
    std::string currDir = fs::current_path();

    std::string testPath = currDir + testDir;
    std::string testTerm = "TODO";
    testEngine.execute(found, testPath, testTerm);

    REQUIRE(found.size() == 2);
    REQUIRE(found[0] == currDir + testDir + "/lower.txt");
}

// Engine Test Recursive
TEST_CASE("Engine Test Recursive", "[engine]")
{
    Core::Engine testEngine(true, true);
    
    std::vector<std::string> found;

    std::string testDir = "/test_files/single";
    std::string currDir = fs::current_path();

    std::string testPath = currDir + testDir;
    std::string testTerm = "TODO";
    testEngine.execute(found, testPath, testTerm);

    REQUIRE(found.size() == 3);
    REQUIRE(found[1] == currDir + testDir + "/folder/single.txt");
}

// Engine Test isSidesSafe
TEST_CASE("Engine isSidesAlphaSafe", "[engine]")
{
    Core::Engine testEngine(false, false);

    std::string term("TODO");
    std::string line("POTODO");
    size_t pos = line.find(term);

    REQUIRE(testEngine.isSidesAlphaSafe(line, pos, term.size()) == false);

    std::string line1("TODOPO");
    pos = line1.find(term);

    REQUIRE(testEngine.isSidesAlphaSafe(line1, pos, term.size()) == false);

    std::string line2("//TODO:");
    pos = line2.find(term);

    REQUIRE(testEngine.isSidesAlphaSafe(line2, pos, term.size()) == true);

    std::string line3("TODO");
    pos = line3.find(term);

    REQUIRE(testEngine.isSidesAlphaSafe(line3, pos, term.size()) == true);
}
