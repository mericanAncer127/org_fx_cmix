#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <cctype>

using namespace std;

// Helper function to trim leading spaces from a string
string ltrim(const string &str)
{
    size_t start = str.find_first_not_of(" \t");
    return (start == string::npos) ? "" : str.substr(start);
}

const std::unordered_map<std::string_view, std::string_view> replacements = {
    {"  <page>", "p&/"},
    {"  </page>", "p^/"},
    {"    <title>", "t&/"},
    {"</title>", "t^/"},
    {"      <comment>", "c&/"},
    {"</comment>", "c^/"},
    {"    </revision>", "e^/"},
    {"      <minor />", "<m/>"},
    {"revision>", "e&/"},
    {"timestamp>", "m&/"},
    {"contributor>", "v&/"},
    {"/contributor>", "v^/"},
    {"username>", "u&/"},
};
std::string processLine(const std::string &line)
{
    std::string modifiedLine = line;

    for (const auto &[oldStr, newStr] : replacements)
    {
        size_t pos = 0;
        while ((pos = modifiedLine.find(oldStr, pos)) != std::string::npos)
        {
            modifiedLine.replace(pos, oldStr.length(), newStr);
            pos += newStr.length();
        }
    }

    return modifiedLine;
}

std::string reverseProcessLine(const std::string &line)
{
    std::string modifiedLine = line;

    for (const auto &[newStr, oldStr] : replacements)
    {
        size_t pos = 0;
        while ((pos = modifiedLine.find(oldStr, pos)) != std::string::npos)
        {
            modifiedLine.replace(pos, oldStr.length(), newStr);
            pos += newStr.length(); // Move position to avoid replacing the same instance
        }
    }

    return modifiedLine;
}

int transformFile()
{
    std::ifstream inputFile(".main_phda9prepr", std::ios::binary);
    if (!inputFile)
    {
        std::cerr << "Error opening input file: " << ".main_phda9prepr" << '\n';
        return -1;
    }

    std::ofstream outputFile(".main_phda9prepr_transformed", std::ios::binary);
    if (!outputFile)
    {
        std::cerr << "Error opening output file: " << ".main_phda9prepr_transformed" << '\n';
        return -1;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        std::string modifiedLine = processLine(line);
        outputFile << modifiedLine << '\n';
    }

    std::cout << "File transformation complete. Output saved to '" << ".main_phda9prepr_transformed" << "'\n";

    return 0;
}

// File transformation function with batch processing
int reverseTransformFile(size_t batchSize = 8192)
{ // Default batch size of 8 KB
    std::ifstream inputFile(".main_decomp", std::ios::binary);
    if (!inputFile)
    {
        std::cerr << "Error opening input file: " << ".main_phda9prepr_transformed" << '\n';
        return -1;
    }

    std::ofstream outputFile(".main_phda9prepr_detransformed", std::ios::binary);
    if (!outputFile)
    {
        std::cerr << "Error opening output file: " << ".main_phda9prepr_detransformed" << '\n';
        return -1;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        std::string modifiedLine = reverseProcessLine(line);
        outputFile << modifiedLine << '\n';
    }

    std::cout << "File transformation complete. Output saved to '" << ".main_phda9prepr_detransformed" << "'\n";

    return 0;
}