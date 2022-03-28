#include "FileReader.h"

    FileReader::FileReader(const std::string& fileName)
    {
        blockCoordsFile = new std::fstream();
        blockCoordsFile->open(fileName, std::ios::in);
    }

    FileReader::~FileReader()
    {
        if (blockCoordsFile)
        {
           delete blockCoordsFile;
        }
       
    }

    void FileReader::AddCoordsToBlock(int* arr, const int arraySize)
    {
        if (blockCoordsFile->is_open())
        {
            std::string line;
            int arrIndex = 0;
            while (std::getline(*blockCoordsFile, line))
            {
                for (unsigned int i = 0; i < line.length() && arrIndex < arraySize; i++)
                {
                    char currentChar = line.at(i);

                    if (currentChar == '5')
                    {
                        arr[arrIndex] = 5;
                        arrIndex++;
                    }
                    else
                    {
                        arr[arrIndex] = 0;
                        arrIndex++;
                    }
                }
            }
        }
        blockCoordsFile->close();
    }

