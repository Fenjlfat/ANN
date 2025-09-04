#pragma once
#include "Header.h"
class PERCEPTRON
{
private:
    int funct{ 2 };
    int layer;
    int neuron;
    int connect;
    int inputData;
    int outputData;
    double koef_DEL;
    double weightMin;
    double weightMax;
    double biasMin;
    double biasMax;
    double alpha;
    double koef_relu;

public:
    //массив весов
    std::vector<std::vector<std::vector<double>>> WEIGHT;
    //массив смещений
    std::vector<std::vector<double>> BIAS;
    //массив сумм 
    std::vector<std::vector<double>> summForFunction;
    //сигнал каждого нейрона
    std::vector<std::vector<double>> signalsNeurons;
    //ошибка каждого нейрона
    std::vector<std::vector<double>> deltaNeurons;

public:
    PERCEPTRON(int functional, int layer_ann, int neuron_ann, int connect_ann,
        int input_Data, int output_Data, double koef_del, double weight_Min, double weight_Max, double bias_Min, double bias_Max, double alfa, double koefRelu);
    ~PERCEPTRON();
    void initialization_Vectors();
    double FORWARD_PROPAGATION(std::vector<double>& input, std::vector<double>& output);
    double ERROR(std::vector<double>& output, std::vector<double>& outputArrayFile);
    double BACK_PROPAGATION(std::vector<double>& input);

};

