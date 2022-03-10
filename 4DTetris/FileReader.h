#pragma once
#include<string>
#include <fstream>

class FileReader
{
private:
    std::fstream* blockCoordsFile = nullptr;

public:
    FileReader(const std::string& fileName);
    ~FileReader();

    void AddCoordsToBlock(int* arr, const int arraySize);
};

