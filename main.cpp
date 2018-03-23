/**
    DataFileStats
    main.cpp
    Purpose: Checks a flat data file, and writes out some statistics to make database import somewhat easier.

    @author Quedlin
    @version 1.0 2018.03.23.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}



int main(int argc, char* argv[])
{


    if (argc != 3)
    {
        std::cerr << "Usage: \t" << argv[0] << " FILENAME DELIMETER" << std::endl;
        std::cerr << "e.g.:\t" << argv[0] << " FILENAME ," << std::endl;
        std::cerr << "  or:\t" << argv[0] << " FILENAME ;" << std::endl;
        std::cerr << "  or:\t" << argv[0] << " FILENAME \\t" << std::endl;
        std::cerr << "  or:\t" << argv[0] << " FILENAME \\space" << std::endl;
        return 1;
    }

    std::string fileName = argv[1];
    std::string delimeter = argv[2];
    char delimeterChar;

    if (delimeter.compare("\\t") == 0)
        delimeterChar = '\t';
    if (delimeter.compare("\\space") == 0)  //TODO: Rethink this later or something
        delimeterChar = ' ';
    else
    {
        if (delimeter.length() != 1)
        {
            std::cerr << "Invalid delimeter." << std::endl;
            return 1;
        }
        delimeterChar = delimeter.c_str()[0];
    }



    int maxLineLength = 0;
    int lineCount = 0;
    std::vector<std::string> headers;
    std::vector<int> maxFieldSizes = std::vector<int>();

    std::ifstream file(fileName);
    std::string str;
    while (std::getline(file, str))
    {

        std::vector<std::string> cells = split(str, delimeterChar);
        if (lineCount == 0)
        {
            headers = cells;

            for (unsigned int i=0; i<headers.size(); i++)
            {
                maxFieldSizes.push_back(0);
            }
        }
        else
        {
            int lineLength = str.length();
            if (lineLength > maxLineLength) maxLineLength = lineLength;

            for (unsigned int k=0; k<cells.size(); k++)
            {
                int cellSize = cells[k].length();
                if (maxFieldSizes[k] < cellSize) maxFieldSizes[k] = cellSize;
            }
        }

        lineCount++;
    }

    cout << endl;
    cout << "Line count: " << lineCount << endl;
    cout << "Maximum line length: " << maxLineLength << endl;
    cout << "Number of fields: " << headers.size() << endl;
    cout << endl;
    for (unsigned int i=0; i<headers.size(); i++)
    {
        cout << "field #" << i << " max size: " << maxFieldSizes[i] << "\t(" << headers[i] << ")" << endl;
    }

    return 0;
}
