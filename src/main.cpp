#include <iostream>
#include "argparser.hpp"
#include "engine.h"
#include <cassert>

/**
 * Initialize our Argument Parser
 * 
 * @param parser
 *      Argument Parser
 **/
void initArgParser(ArgParse::ArgParser &parser)
{
    ArgParse::ArgParserConfigs configs;
    configs.push_back(
        ArgParse::ArgParserConfigType(
            "-nr", "-norecursion", false, 
            "Without Recursion ", 
            [](ArgParse::ArgParserValues value, const char* argv)
            {
                assert(argv == nullptr);
                value.m_boolValue = true; 
                return value;
            }));
    configs.push_back(
        ArgParse::ArgParserConfigType(
            "-i", "-insensitive", false, 
            "Case Insensitive Lookup", 
            [](ArgParse::ArgParserValues value, const char* argv)
            {
                assert(argv == nullptr);
                value.m_boolValue = true;
                return value;
            }));
    configs.push_back(
        ArgParse::ArgParserConfigType(
            "-d", "-directory", true, 
            "Directory to look within (must be absolute path)", 
            [](ArgParse::ArgParserValues value, const char* argv)
            {
                value.m_charValue = argv;
                return value;
            }));
    configs.push_back(
        ArgParse::ArgParserConfigType(
            "-h", "-help", false, 
            "Help Text", 
            [](ArgParse::ArgParserValues value, const char* argv)
            {
                assert(argv == nullptr);
                value.m_boolValue = true;
                return value;
            }));

    parser.loadConfig(configs);
}

int main(int argc, const char* argv[])
{
    // Arguement Parser
    // Initialise the config
    ArgParse::ArgParser parser;
    initArgParser(parser);

    // Parse the configs
    if (!parser.parseArgs(argc, argv))
    {
        std::cerr << "Invalid Option used." << std::endl;
        return 0;
    }

    // Help
    if (parser.contains("-h"))
    {
        std::string help;
        parser.getHelp(help);

        std::cout << help << std::endl;

        return 0;
    }

    std::string location;
    if (parser.contains("-d"))
    {
        location = parser.getValue("-d").m_charValue;
    }

    bool insensitive = false;
    if (parser.contains("-i"))
    {
        insensitive = true;
    }

    bool recursion = true;
    if (parser.contains("-nr"))
    {
        recursion = false;
    }

    // Search Term
    std::string term("TODO");
    
    // Create Engine
    Core::Engine engine(insensitive, recursion);

    std::vector<std::string> found;
    engine.execute(found, location, term);

    for (auto &file : found)
    {
        std::cout << file << std::endl;
    }
    
    return 0;
}
