#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

namespace Core 
{

class Engine 
{
public:
    
    /**
     * Constructor of Engine
     * 
     * @param term
     *      Search Term
     * 
     * @param location
     *      Search Location
     * 
     * @param insensitive
     *      Flag for case insensitive
     * 
     * @param recursion
     *      Flag for recursion
     * 
     **/
    Engine(bool insensitive, bool recursion) :
        m_insensitive(insensitive),
        m_recursion(recursion)
    {
        // Do nothing
    }
    // Destructor
    ~Engine()
    {
        // Do nothing
    }

    // Flag Insensitive Search
    bool m_insensitive;

    // Flag Recursion
    bool m_recursion;

    /**
     *  Execute Function
     * 
     * @param found
     *      list of files found
     * 
     **/
    void execute(std::vector<std::string> &found, std::string &location, std::string &term);

    /**
     * Prints Error Message
     * 
     * @param error
     *      the error message
     * 
     **/
    inline void printError(std::string error)
    {
        std::cerr << "Error: " << error << std::endl;
    }

    /**
     * Checks Left and Right of the String to not be alpha
     * 
     * @param line
     *      line we are checking
     * 
     * @param pos
     *      found position
     * 
     * @param size
     *      size of the term we were searching
     **/
     bool isSidesAlphaSafe(std::string &line, size_t pos, size_t size);

private:

    /**
     * Select the correct location
     * If the userlocation is invalid, 
     * We will use the current path for the search location
     * 
     * @param userLocation
     *      User Location to check
     * 
     * @return 
     *      true if path exists
     **/
    bool selectLocation(fs::path &searchLocation, std::string &userLocation);

    /**
     * Retrieve the files under the search location
     * 
     * @param filePaths
     *      paths of the files under the location
     * 
     **/
    void retrieveFiles(std::vector<fs::path> &filePaths, fs::path &searchLocation);
    
};  // Class Engine

}    // Namespace Core

#endif //ENGINE_H