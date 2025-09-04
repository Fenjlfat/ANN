#include "PERCEPTRON.h"
#include "Header.h"




PERCEPTRON::PERCEPTRON(int functional, int layer_ann, int neuron_ann, int connect_ann,
    int input_Data, int output_Data, double koef_del, double weight_Min, double weight_Max, double bias_Min, double bias_Max, double alfa, double koefRelu)
{
    funct = functional;
    layer = layer_ann;
    neuron = neuron_ann;
    connect = connect_ann;
    inputData = input_Data;
    outputData = output_Data;
    koef_DEL = koef_del;
    weightMin = weight_Min;
    weightMax = weight_Max;
    biasMin = bias_Min;
    biasMax = bias_Max;
    alpha = alfa;
    koef_relu = koefRelu;
}

PERCEPTRON::~PERCEPTRON()
{
}

double function(double t, double koef_relu, std::string name_function)
{
    if (name_function == "RELU")
    {
        if (t >= 0)
        {
            return t;
        }
        else
        {
            return t * koef_relu;
        }
    }

    if (name_function == "Dif_RELU")
    {
        if (t >= 0)
        {
            return 1;
        }
        else
        {
            return  koef_relu;
        }
    }

    //сигмоидальная функция
    if (name_function == "sigmoid")
    {
        return (1 / (1 + exp(-t)));
    }

    //производная сигмоидальной функции
    if (name_function == "dif_sigmoid")
    {
        return ((1 / (1 + exp(-t))) * (1 - (1 / (1 + exp(-t)))));
    }

}

//инициализации векторов
void PERCEPTRON::initialization_Vectors()
{
    //инициализация весов
    std::cout << "initialization  weight" << std::endl;
    for (int i = 0; i < layer; i++)
    {
        std::vector<std::vector<double>> arr;
        for (int j = 0; j < neuron; j++)
        {
            std::vector<double> vec;
            for (int k = 0; k < connect; k++)
            {
                vec.push_back(((double)(rand()) / RAND_MAX * (weightMax - weightMin) + weightMin) / koef_DEL);
            }
            arr.push_back(vec);
            vec.clear();
        }
        WEIGHT.push_back(arr);
        arr.clear();
    }
    /*
    for (int i = 0; i < layer; i++)
    {
        std::cout << "beg layer = " << i << std::endl;
        for (int j = 0; j < neuron; j++)
        {
            std::cout << "beg neuron = " << j << std::endl;
            for (int k = 0; k < connect; k++)
            {
                std::cout << WEIGHT[i][j][k];
            }
            std::cout << "\n end neuron = " << j << std::endl;
        }
        std::cout << "\n end layer = " << i << std::endl;
    }
    getchar();
    */
    //инициализация смещений
    std::cout << "initialization  bias" << std::endl;
    for (int i = 0; i < layer; i++)
    {
        std::vector<double> vec;
        if (i < layer - 1)
        {
            for (int j = 0; j < neuron; j++)
            {
                double x = ((double)(rand()) / RAND_MAX * (biasMax - biasMin) + biasMin) / koef_DEL;
                vec.push_back(x);
            }
        }
        else
        {
            for (int j = 0; j < neuron; j++)
            {
                vec.push_back(0.00);
            }
        }

        BIAS.push_back(vec);
        vec.clear();
    }

    //intializationn summForFunction
    //intializationn сигнал каждого нейрона
    //инициализация масива ошибок нейронов
    std::cout << "initialization  summForFunction" << std::endl;
    for (int i = 0; i < layer; i++)
    {
        std::vector<double> vec;
        for (int j = 0; j < neuron; j++)
        {
            vec.push_back(0.00);
        }
        summForFunction.push_back(vec);    //intializationn summForFunction
        signalsNeurons.push_back(vec);     //intializationn сигнал каждого нейрона
        deltaNeurons.push_back(vec);       //инициализация масива ошибок нейронов
        vec.clear();
    }
}

//прямое распространение
double PERCEPTRON::FORWARD_PROPAGATION(std::vector<double>& input, std::vector<double>& output)
{
    double summa = 0.00;
    int z = 0;

    //инициализация сигналов входного слоя
    //cout << "initialization input signals" << endl;
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < neuron; j++)
        {
            for (int k = 0; k < connect; k++)
            {
                summa += input[k] * WEIGHT[i][j][k];
            }
            summa = summa + BIAS[i][j];
            summForFunction[i][j] = summa;
            signalsNeurons[i][j] = function(summa, koef_relu, "sigmoid");
            summa = 0.00;
        }
    }
    //вычисление сигналов нейронов для скрытого и выходного слоев
    for (int i = 1; i < layer; i++)
    {
        for (int j = 0; j < neuron; j++)
        {
            z = layer - i;
            for (int k = 0; k < connect; k++)
            {
                summa += signalsNeurons[i - 1][k] * WEIGHT[i][j][k];
            }
            summa = summa + BIAS[i][j];
            summForFunction[i][j] = summa;
            if (z == 1)
            {
                signalsNeurons[i][j] = function(summa, koef_relu, "sigmoid");
            }
            else
            {
                if (funct == 1)
                {
                    signalsNeurons[i][j] = function(summa, koef_relu, "sigmoid");
                }
                if (funct == 2)
                {
                    signalsNeurons[i][j] = function(summa, koef_relu, "RELU");
                }
            }
            summa = 0.00;
            z = 0;
        }

        z = layer - i;
        //вычисление выходного слоя
        if (z == 1)
        {
            for (int n = 0; n < outputData; n++)
            {
                output[n] = signalsNeurons[i][n];
            }
        }
        z = 0;

    }
    return  0;
}

//вычисление ошибок
double PERCEPTRON::ERROR(std::vector<double>& output, std::vector<double>& outputArrayFile)
{
    double proverka = 0.0;
    double summaDelta = 0.00;

    //ошибки выходного слоя
    for (int n = 0; n < outputData; n++)
    {
        deltaNeurons[layer - 1][n] = (-outputArrayFile[n] / output[n] + (1 - outputArrayFile[n]) / (1 - output[n])) * function(summForFunction[layer - 1][n], koef_relu, "dif_sigmoid");
    }

    //ошибки нейронов
    for (int i = layer - 2; i >= 0; i--)
    {
        for (int n = 0; n < neuron; n++)
        {
            summaDelta = 0.00;
            for (int k = 0; k < connect; k++)
            {
                summaDelta += deltaNeurons[i + 1][k] * WEIGHT[i + 1][n][k];
            }
            double x{ 0.00 };
            if (funct == 1)
            {
                double x = function(summForFunction[i][n], koef_relu, "dif_sigmoid");
                deltaNeurons[i][n] = summaDelta * x;
            }
            if (funct == 2)
            {
                x = function(summForFunction[i][n], koef_relu, "Dif_RELU");
                deltaNeurons[i][n] = summaDelta * x;
            }

        }
    }

    return 0;
}

//обратное распространение
double PERCEPTRON::BACK_PROPAGATION(std::vector<double>& input)
{
    double znachenie = 0.00;
    //вычисление весовых коэффициентов для входного слоя
    for (int i = 0; i < 1; i++)
    {
        for (int n = 0; n < neuron; n++)
        {
            for (int k = 0; k < connect; k++)
            {
                WEIGHT[i][n][k] = WEIGHT[i][n][k] - (alpha * deltaNeurons[i][n] * input[k]);
            }
        }
    }
    //вычисление весовых коэффициентов для скрытого и выходного слоев
    for (int i = 1; i < layer; i++)
    {
        for (int n = 0; n < neuron; n++)
        {
            for (int k = 0; k < connect; k++)
            {
                WEIGHT[i][n][k] = WEIGHT[i][n][k] - (alpha * deltaNeurons[i][n] * signalsNeurons[i - 1][k]);
            }
        }
    }
    //вычисление смещений
    for (int i = 0; i < layer; i++)
    {
        for (int n = 0; n < neuron; n++)
        {
            BIAS[i][n] = BIAS[i][n] - alpha * deltaNeurons[i][n];
        }
        //cout << endl;
    }

    return 0;
}
