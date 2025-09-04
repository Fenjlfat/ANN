#pragma once
#include "Header.h"

//параметры нейросети
struct PARAMETRS_ANN
{
    int layer = 4;
    int neuron = 32;
    int connect = 32;

    int input_Data = 3;
    int output_Data = 2;
    int columns_File = 5;

    int function = 2; //function activation 1=sigmoidal, 2=ReLU
    int epochs = 100000;
    int counter = 100000;      // show graphycs after number of epochs
    int BEGIN_batch = 0;//начало батча
    int END_batch = 100;//конец батча
    double tochnost = 0.0001;
    double alpha = 0.01;
    double koef_relu = 0.05;
    //double koef_relu = 0.02;
    double koef_normirovki = 0.1;
    //double koef_DEL = 10.00;
    double koef_DEL = 10.00;
    double weightMin = -0.8, weightMax = 0.95;  //initial range of weights
    double biasMin = -0.5, biasMax = 0.94;       //initial range of biases
    //string name_File = "SPH_CU_CUBE_V1D5_L5_R18_T300_X.txt";

    std::string name_File = "ANN_ALL_SPH_MM_CU_V1D5_1_POR_random.txt";

    std::string nameFileGnuplot = "DataGnuplot.txt";
    std::string way_to_DataGnuplot = "D:\\WORK\\SPH\\PROGRAMMS\\C++\\ANN\\ANN\\";

    std::string plot_1 = "1:2";   // SXX_MD
    std::string plot_2 = "1:3";   // POR_MD

    std::string plot_3 = "1:4";   // SXX_ANN
    std::string plot_4 = "1:5";   // POR_ANN
};
extern PARAMETRS_ANN PAR;