#include "Header.h"
#include "FileHandling.h"


FileHandling::FileHandling(std::string name_File, int columns_File, int input_Data, int output_Data)
{
    nameFile = name_File;
    columnsFile = columns_File;
    inputData = input_Data;
    outputData = output_Data;
}

FileHandling::~FileHandling()
{
}

int FileHandling::processingFile()
{
    int  l = 0;
    double q = 0;

    std::fstream FILE;

    //считываем данные с файла в вектор‘айл
    FILE.open(nameFile, std::ios::in);
    if (!FILE.is_open())
    {
        std::cout << "File not open" << std::endl;
    }
    else
    {
        std::cout << "File open" << std::endl;
        while (!FILE.eof())
        {
            std::vector<double> vectorLine;
            for (int i = 0; i < columnsFile; i++)
            {
                FILE >> q;
                vectorLine.push_back(q);
            }
            vectorFile.push_back(vectorLine);
            vectorLine.clear();
            // считывем количество точек файла
            l = l + 1;
            //std::cout << l << std::endl;
        }
    }
    FILE.close();
    numberPoint = l;

    //распредел€ем векторфайл во входной и выходной векторы
    for (int i = 0; i < numberPoint; i++)
    {
        std::vector<double> vectorFileInput;
        for (int n = 0; n < inputData; n++)
        {
            vectorFileInput.push_back(vectorFile[i][n]);
        }
        vectorInput.push_back(vectorFileInput);
        vectorFileInput.clear();
    }
    for (int i = 0; i < numberPoint; i++)
    {
        std::vector<double> vectorFileOutput;
        for (int n = 0; n < outputData; n++)
        {
            vectorFileOutput.push_back(abs(vectorFile[i][n + inputData]));
        }
        vectorOutput.push_back(vectorFileOutput);
        vectorFileOutput.clear();
    }

    return numberPoint;
}

