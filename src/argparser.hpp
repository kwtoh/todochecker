#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <functional>

namespace ArgParse
{

// Type Definition for Values
typedef union Values 
{
    // boolean arguement value
    bool m_boolValue;

    // integer arguement value
    int m_intValue;

    // string arguement value
    const char * m_charValue;
} ArgParserValues;

// Type Definition for Argument Parser Config
typedef struct Config
{
    Config(const char *shortform, const char *longform, 
        bool isValued, const char *description, 
        std::function<ArgParserValues(ArgParserValues, const char*)> setter) : 
        m_short(shortform),
        m_long(longform),
        m_valued(isValued),
        m_description(description),
        m_setter(setter)
    {
        // Do Nothing
    }

    // short form for arg
    std::string m_short;

    // long form for arg
    std::string m_long;

    // flag to indicate if arg needs a value
    bool m_valued;

    // Description of arg
    std::string m_description;

    // Setter of the function
    std::function<ArgParserValues(ArgParserValues, const char*)> m_setter;

} ArgParserConfigType;

// Type Definition for vector of configs
typedef std::vector<ArgParserConfigType> ArgParserConfigs;

class ArgParser 
{

public:

    // Type Definition for Map that contains of all the arguments parsed.
    typedef std::unordered_map<std::string, ArgParserValues> ArgParserMap;

    // Arguement Parser Map
    ArgParserMap m_argMap;

    // Arguement Parser Config
    ArgParserConfigs m_argConfig;

    // Constructor
    ArgParser() :
        m_argMap(),
        m_argConfig()
    {
        // Do Nothing
    }

    ~ArgParser()
    {
        m_argMap.clear();
        m_argConfig.clear();
    }

    /**
     * load the Configuration into the Parser
     * 
     * @param config
     *     config with the information on what parameters exists
     * 
     **/
    void loadConfig(ArgParserConfigs &config)
    {
        m_argConfig = std::move(config);
    }

    /**
     * Parses the Arguments into a Map for quick reference.
     * 
     * @param argc
     *      Argument Count
     * 
     * @param argv
     *      Argument Values
     **/
    bool parseArgs(int argc, const char* argv[])
    {
        if (argc < 1)
        {
            return false;
        }

        // We are ignoring 1 as that would be the program name
        for (int i = 1; i < argc; ++i)
        {
            bool found = false;
            std::string arg(argv[i]);
            for (auto &config : m_argConfig)
            {
                // We will process the argument
                if ((arg.compare(config.m_short) == 0) || (arg.compare(config.m_long) == 0))
                {
                    found = true;
                    ArgParserValues val;
                    if (config.m_valued)
                    {
                        // Check that we have enough arguments
                        if (argc > i + 1)
                        {
                            m_argMap[config.m_short] = config.m_setter(val, argv[++i]);
                        }
                        else
                        {
                            found = false;
                        }
                        
                    }
                    else
                    {
                        m_argMap[config.m_short] = config.m_setter(val, nullptr);
                    }
                    break;
                }
            }

            if (!found)
            {
                return false;
            }
        }

        return true;
    }

    /// Returns Help String from the argument list.
    void getHelp(std::string &help)
    {
        help = "Help Text\n";
        for (auto &config : m_argConfig)
        {
            help += config.m_short;
            help += "\t\t";
            help += config.m_long;
            help += "\t\t";
            help += config.m_description;
            help += "\n";
        }
    }

    /// Check Parser Map for Parameters
    bool contains(const char *arg)
    {
        std::string argStr(arg);
        return m_argMap.count(argStr);
    }

    /// Returns Arg Parser Values
    inline ArgParserValues getValue(const char *arg)
    {
        return m_argMap[arg];
    }

    
};

}
