#include<stdio.h> 
#include<stdlib.h> 
#include <string>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> 
#include <chrono> 
#include <sstream>
#include <tchar.h>
using namespace std::chrono;
using namespace std;



size_t binarySearch(std::vector<std::string>* arr, string x, size_t n)
{
    size_t l = 0;
    size_t r = n - 1;
    while (l <= r)
    {
        size_t m = l + (r - l) / 2;

        size_t res;

        if (x == ((*arr)[m]))
            res = 0;


        // Check if x is present at mid 
        if (res == 0)
            return m;

        // If x greater, ignore left half 
        if (x > ((*arr)[m]))
            l = m + 1;

        // If x is smaller, ignore right half 
        else
            r = m - 1;
    }

    return -1;
}

std::vector<std::string> split(std::string strToSplit, char delimeter)
{
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimeter))
    {
        splittedStrings.push_back(item);
    }
    return splittedStrings;
}

bool getFileContent(std::string fileName, std::vector<std::string>& vecOfStrs)
{

	// Open the File
	std::ifstream in(fileName.c_str());

	// Check if object is valid
	if (!in)
	{
		std::cerr << "Cannot open the File : " << fileName << std::endl;
		return false;
	}

	std::string str;
	// Read the next line from File untill it reaches the end.
	while (std::getline(in, str))
	{
		// Line contains string of length > 0 then save it in vector
		if (str.size() > 0)
			vecOfStrs.push_back(str);
	}

	//Close The File
	in.close();
	return true;
}

// Driver Program to test above functions 
int main()
{

    std::ofstream log("logfile.txt", std::ios_base::app | std::ios_base::out);
    std::vector<std::string> hashlistfull;
	std::vector<std::string> hashlist;
    std::vector<std::string> dict;

	auto start = high_resolution_clock::now();

	bool result = getFileContent("hashlist.txt", hashlistfull);
    bool dictresult = getFileContent("dict.txt", dict);


    auto duration = duration_cast<seconds>(high_resolution_clock::now() - start);

    cout << "Time taken to Read Files: "
        << duration.count() << " seconds" << endl;

	if (result)
	{
		for (std::string& line : hashlistfull)
			hashlist.push_back(line.substr(0, 8));
	}

    cout << "Hashlist Processing Done: "
        << hashlist[hashlistfull.size() - 1] << " -" << endl;

    if (result)
    {
        __int64 i = 0;
        for (std::string& line : dict)
        {
            if (line.length() <= 82)
                continue;
            vector <string> tokens;

            stringstream check1(line);

            string intermediate;

            try
            {
                while (getline(check1, intermediate, ':'))
                {
                    tokens.push_back(intermediate);
                }
            }
            catch (int e)
            {
                continue;
            }

            i++;

            if (tokens[0].find('@') == -1)
                continue;
            if (tokens[1].length() <= 39)
                continue;

            size_t index = binarySearch(&hashlist, tokens[1].substr(0, 8), hashlist.size());
            if (index == -1)
                continue;
            log << tokens[0]  << hashlistfull[index].substr(81) << "\n";

            SetConsoleTitle(to_wstring(i).c_str());
        }
    }
    log.close();

    cout << "End" << endl;

    getchar();
    return 0;
}
