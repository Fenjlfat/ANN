#include "Header.h"
#include "DataNormalisation.h"
//нормировка переменных

DataNormalisation::DataNormalisation(int number_Point, int input_Data, int output_Data, double koef_norm,
    std::vector<std::vector<double>> vector_Input, std::vector<std::vector<double>> vector_Output)
{
    numberPoint = number_Point;
    inputData = input_Data;
    outputData = output_Data;
    koefNormirovki = koef_norm;
    vectorInput = vector_Input;
    vectorOutput = vector_Output;
}

double Normirovka(double X, double Xmin, double Xmax, double koefNormirovki)
{
    double s = 0.00;
    double ret = 0.00;

    if (Xmax != Xmin)
    {
        s = (Xmax - Xmin) * koefNormirovki;
        Xmin = Xmin - s;
        Xmax = Xmax + s;
        ret = (X - Xmin) / (Xmax - Xmin);
    }
    else
    {
        s = Xmax * koefNormirovki;
        Xmin = Xmin - s;
        Xmax = Xmax + s;
        ret = (X - Xmin) / (Xmax - Xmin);
    }
    if (Xmax == 0 || Xmin == 0)
    {
        ret = 0.00;
    }
    //Xmin = Xmin - s;
    //Xmax = Xmax + s;
    //return (X - Xmin) / (Xmax - Xmin);
    return ret;
}
double Perenormirovka(double Ynorm, double Ymin, double Ymax, double koefNormirovki)
{
    double s = 0.00;
    s = (Ymax - Ymin) * koefNormirovki;
    Ymin = Ymin - s;
    Ymax = Ymax + s;
    return Ynorm * (Ymax - Ymin) + Ymin;
    //return Ynorm * (Ymax - Ymin - Ymin * 0.2) + Ymin + Ymin * 0.2;

}

//нормируем входной и выходной вектор
double DataNormalisation::NORMIROVKA()
{

    //определение максимальных и минимальных значений для нормировки
    for (int j = 0; j < inputData; j++)
    {
        min_Input.push_back(vectorInput[0][j]);
        max_Input.push_back(vectorInput[0][j]);
    }
    for (int j = 0; j < outputData; j++)
    {
        min_Output.push_back(vectorOutput[0][j]);
        max_Output.push_back(vectorOutput[0][j]);
    }
    for (int i = 0; i < numberPoint; i++)
    {
        for (int j = 0; j < inputData; j++)
        {
            if (vectorInput[i][j] < min_Input[j])
            {
                min_Input[j] = vectorInput[i][j];
                /*if (vectorInput[i][5] == 0.0)
                {
                    //cout << "i=" << i;
                    //getchar();
                }*/
            }
            if (vectorInput[i][j] > max_Input[j])
            {
                max_Input[j] = vectorInput[i][j];
            }
        }
        for (int j = 0; j < outputData; j++)
        {
            if (vectorOutput[i][j] < min_Output[j])
            {
                min_Output[j] = vectorOutput[i][j];
            }
            if (vectorOutput[i][j] > max_Output[j])
            {
                max_Output[j] = vectorOutput[i][j];
            }
        }
    }

    for (int i = 0; i < numberPoint; i++)
    {
        std::vector<double> vecInNorm;
        for (int j = 0; j < inputData; j++)
        {
            vecInNorm.push_back(Normirovka(vectorInput[i][j], min_Input[j], max_Input[j], koefNormirovki));
        }
        vectorInputNorm.push_back(vecInNorm);
        vecInNorm.clear();

        std::vector<double> vecOutNorm;
        for (int j = 0; j < outputData; j++)
        {
            vecOutNorm.push_back(Normirovka(vectorOutput[i][j], min_Output[j], max_Output[j], koefNormirovki));
        }
        vectorOutputNorm.push_back(vecOutNorm);
        vecOutNorm.clear();
    }

    return 0;
}