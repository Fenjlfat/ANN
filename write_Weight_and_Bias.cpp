#include "parametrs.h"
//запись весовых коэффициентов и смещений в файл
void write_Weight_and_Bias(std::vector<std::vector<std::vector<double>>>& WEIGHT, std::vector<std::vector<double>>& BIAS,
    std::vector<double>& min_Input, std::vector<double>& max_Input, std::vector<double>& min_Output, std::vector<double>& max_Output)
{
    PARAMETRS_ANN PARAMETR;
    std::ofstream fileweghts;
    fileweghts.open("koefficientsWeightOut.txt");
    if (fileweghts.is_open())
    {
        for (int i = 0; i < PARAMETR.layer; i++)
        {
            for (int n = 0; n < PARAMETR.neuron; n++)
            {
                for (int k = 0; k < PARAMETR.connect; k++)
                {
                    fileweghts << WEIGHT[i][n][k] << "   ";
                }
                fileweghts << std::endl;
            }
            //file << endl;
        }
    }
    fileweghts.close();

    std::ofstream filebias;
    filebias.open("koefficientsBiasOut.txt");
    if (filebias.is_open())
    {
        for (int i = 0; i < PARAMETR.layer; i++)
        {
            for (int n = 0; n < PARAMETR.neuron; n++)
            {
                filebias << BIAS[i][n] << "   ";
            }
            filebias << std::endl;
        }
    }
    filebias.close();

    std::ofstream file;
    file.open("minInput.txt");
    if (file.is_open())
    {
        for (int i = 0; i < PARAMETR.input_Data; i++)
        {
            file << min_Input[i] << "   ";
        }
    }
    file.close();
    file.open("maxInput.txt");
    if (file.is_open())
    {
        for (int i = 0; i < PARAMETR.input_Data; i++)
        {
            file << max_Input[i] << "   ";
        }
    }
    file.close();
    file.open("minOutput.txt");
    if (file.is_open())
    {
        for (int i = 0; i < PARAMETR.output_Data; i++)
        {
            file << min_Output[i] << "   ";
        }
    }
    file.close();
    file.open("maxOutput.txt");
    if (file.is_open())
    {
        for (int i = 0; i < PARAMETR.output_Data; i++)
        {
            file << max_Output[i] << "   ";
        }
    }
    file.close();

}