#pragma once
#include "Header.h"

class DataNormalisation
{
public:
    int numberPoint;
    int inputData;
    int outputData;
    double koefNormirovki;
    std::vector<std::vector<double>> vectorInput;     //инициализация вектора входных значений
    std::vector<std::vector<double>> vectorOutput;    //инициализация вектора выходных значений
    std::vector<double> min_Input;
    std::vector<double> max_Input;
    std::vector<double> min_Output;
    std::vector<double> max_Output;
    std::vector<std::vector<double>> vectorInputNorm;
    std::vector<std::vector<double>> vectorOutputNorm;
public:
    DataNormalisation(int number_Point, int input_Data, int output_Data, double koef_norm, std::vector<std::vector<double>> vectorInput, std::vector<std::vector<double>> vectorOutput);
    double NORMIROVKA();
};
