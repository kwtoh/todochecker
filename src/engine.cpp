#include "engine.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cctype>

namespace Core
{
bool Engine::selectLocation(fs::path &searchLocation, std::string &userLocation)
{
    if (!userLocation.empty())
    {
        if (fs::exists(fs::path(userLocation)))
        {
            searchLocation = fs::path(userLocation);
        }
        else
        {
            return false;
        }
    }
    else
    {
        searchLocation = fs::current_path();
    }

    return true;
}

void Engine::retrieveFiles(std::vector<fs::path> &filePaths, fs::path &searchLocation)
{
    if (m_recursion)
    {
        for (auto &file : fs::recursive_directory_iterator(searchLocation))
        {
            filePaths.push_back(file.path());
        }
    }
    else
    {
        for (auto &file : fs::directory_iterator(searchLocation))
        {
            filePaths.push_back(file.path());
        }
    }
}

void Engine::execute(std::vector<std::string> &found, std::string &location, std::string &term)
{
    fs::path searchLocation;
    selectLocation(searchLocation, location);

    std::vector<fs::path> paths;
    retrieveFiles(paths, searchLocation);

    for (auto &file : paths)
    {
        std::ifstream input(file);
        if (!input.is_open())
        {
            // We will continue the execution if a single file is not found
            // However, we will log an error to inform the user.
            std::string error(file);
            error += " not found.";
            printError(error);
            continue;
        }
        
        bool result = false;
        std::string line;
        while (std::getline(input, line))
        {
            if (term.size() > line.size())
            {
                continue;
            }

            if (m_insensitive)
            {
                auto it = std::search(
                    line.begin(), line.end(), term.begin(), term.end(),
                    [](char ch1, char ch2)
                    {
                        return std::tolower(ch1) == std::tolower(ch2);
                    }
                );

                if (it != line.end())
                {
                    // We will try to check that this word is isolated
                    // By checking that no alpha is next to it.
                    result = isSidesAlphaSafe(line, it - line.begin(), term.size());
                    break;
                }
            }
            else
            {
                size_t pos = line.find(term.c_str());
                if (pos != std::string::npos)
                {
                    result = isSidesAlphaSafe(line, pos, term.size());
                    break;
                }
            }
        }

        if (result)
        {
            found.push_back(file);
        }

        input.close();

    }

}

bool Engine::isSidesAlphaSafe(std::string &line, size_t pos, size_t size)
{
    // We will try to check that this word is isolated
    // By checking that no alpha is next to it
    assert(pos < line.size());

    bool isLeftOk = false;
    if (pos == 0 || !std::isalpha(line[pos - 1]))
    {
        isLeftOk = true;
    }

    bool isRightOk = false;
    if (pos+size == line.size() || !std::isalpha(line[pos+size]))
    {
        isRightOk = true;
    }

    return isLeftOk & isRightOk;
}

} // Namespace Core


    