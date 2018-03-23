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



int main()
{
    //cout << "Hello world!" << endl;

    //std::string fileName = "datafile.txt"

    int maxLineLength = 0;
    int lineCount = 0;
    std::vector<std::string> headers;
    std::vector<int> maxFieldSizes = std::vector<int>();

    std::ifstream file("datafile.txt");
    std::string str;
    while (std::getline(file, str))
    {
        //cout << str << endl;

        std::vector<std::string> cells = split(str, '\t');
        if (lineCount == 0)
        {
            headers = cells;

            for (int i=0; i<headers.size(); i++)
            {
                maxFieldSizes.push_back(0);
            }
        }
        else
        {
            int lineLength = str.length();
            if (lineLength > maxLineLength) maxLineLength = lineLength;

            //cout << "-Number of fields: " << cells.size() << endl;

            for (int k=0; k<cells.size(); k++)
            {
                int cellSize = cells[k].length();
                //cout << "--Cell size: " << cellSize << endl;
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
    for (int i=0; i<headers.size(); i++)
    {
        cout << "field #" << i << " max size: " << maxFieldSizes[i] << endl;
    }


    //std::vector<std::string> x = split("one:two::three", ':');
    //cout << x.size() << endl;


    return 0;
}
