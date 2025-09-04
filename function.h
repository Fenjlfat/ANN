#pragma once
#include "Header.h"

double GNUPLOT(std::string nameFileGnuplot,
    std::string wayToFile,
    std::vector<std::vector<double>>& vector_Output,
    std::vector<std::vector<double>>& vector_MODEL,
    std::string graph1,
    std::string graph2);

void write_Weight_and_Bias(std::vector<std::vector<std::vector<double>>>& WEIGHT, std::vector<std::vector<double>>& BIAS,
    std::vector<double>& min_Input, std::vector<double>& max_Input, std::vector<double>& min_Output, std::vector<double>& max_Output);
