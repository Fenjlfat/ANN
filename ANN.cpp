// ANN.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

// ANN_SPH.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// NEURONKA_MG.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include "Header.h"
#include "function.h"
#include "parametrs.h"
#include "FileHandling.h"
#include "DataNormalisation.h"
#include "PERCEPTRON.h"


int main()
{
    int koord{ 0 };
    double write_error{ 1.00 };

    PARAMETRS_ANN PAR;

    //обработка файла
    FileHandling file{ PAR.name_File,PAR.columns_File,PAR.input_Data, PAR.output_Data };
    file.processingFile();
    int numberPoint = file.numberPoint;
    //нормировка
    DataNormalisation data{ file.numberPoint, PAR.input_Data, PAR.output_Data, PAR.koef_normirovki, file.vectorInput, file.vectorOutput };
    data.NORMIROVKA();

    PERCEPTRON perceptron{ PAR.function, PAR.layer,PAR.neuron, PAR.connect,
        PAR.input_Data, PAR.output_Data, PAR.koef_DEL, PAR.weightMin, PAR.weightMax, PAR.biasMin, PAR.biasMax, PAR.alpha, PAR.koef_relu };
    perceptron.initialization_Vectors();

    //входные значения нейросети
    std::vector<double> input(PAR.neuron, 0.00);
    //выходные значения нейросети
    std::vector<double> output(PAR.output_Data, 0.00);
    std::vector<std::vector<double>> vector_Output_ANN(numberPoint, std::vector<double>(PAR.neuron, 0.00));
    //вектор выходных данных из файла для проверки выходных значений нейросети
    std::vector<double> outputArrayFile(PAR.output_Data, 0);

    int q = 0;
    int min_epoch = 0;
    double Error_AVERAGE = 0.00;
    double Min_Error = 1000.00;
    //прогонка нейросети по эпохам
    for (int f = 1; f <= PAR.epochs; f++)
    {
        //через мини-батчи
        for (int i = PAR.BEGIN_batch; i < PAR.END_batch; i++)
        {
            koord = rand() % numberPoint;

            for (int n = 0; n < PAR.input_Data; n++)
            {
                input[n] = data.vectorInputNorm[koord][n];
            }
            for (int n = 0; n < PAR.output_Data; n++)
            {
                outputArrayFile[n] = data.vectorOutputNorm[koord][n];
            }
            //в персептроне производим прямое распространение  
            perceptron.FORWARD_PROPAGATION(input, output);

            //в персептроне высчитываем ошибки
            perceptron.ERROR(output, outputArrayFile);

            //в персептроне производим обратное распространение
            perceptron.BACK_PROPAGATION(input);
        }

        //расчет ошибки после каждой эпохи
        for (int d = 0; d < numberPoint; d++)
        {
            for (int y = 0; y < PAR.input_Data; y++)
            {
                input[y] = data.vectorInputNorm[d][y];
            }
            //в персептроне производим прямое распространение
            perceptron.FORWARD_PROPAGATION(input, output);
            for (int h = 0; h < PAR.output_Data; h++)
            {
                vector_Output_ANN[d][h] = output[h];
            }
        }
        for (int c = 0; c < numberPoint; c++)
        {
            for (int r = 0; r < PAR.output_Data; r++)
            {
                Error_AVERAGE += pow((data.vectorOutputNorm[c][r] - vector_Output_ANN[c][r]), 2);
            }
        }
        Error_AVERAGE = Error_AVERAGE / (numberPoint * PAR.output_Data);
        if (Error_AVERAGE < Min_Error)
        {
            Min_Error = Error_AVERAGE;
            min_epoch = f;
        }

        //показ графиков после определенной эпохи
        q = q + 1;
        if (q == PAR.counter)
        {
            GNUPLOT(PAR.nameFileGnuplot, PAR.way_to_DataGnuplot, data.vectorOutputNorm, vector_Output_ANN, PAR.plot_1, PAR.plot_3);
            GNUPLOT(PAR.nameFileGnuplot, PAR.way_to_DataGnuplot, data.vectorOutputNorm, vector_Output_ANN, PAR.plot_2, PAR.plot_4);
            write_Weight_and_Bias(perceptron.WEIGHT, perceptron.BIAS, data.min_Input, data.max_Input, data.min_Output, data.max_Output);


            q = 0;
        }
        //показ графиков при заданной точности
        if (Error_AVERAGE < PAR.tochnost)
        {
            //GNUPLOT(PAR.nameFileGnuplot, PAR.way_to_DataGnuplot, data.vectorOutputNorm, vector_Output_ANN, PAR.plot_1, PAR.plot_8);

            write_Weight_and_Bias(perceptron.WEIGHT, perceptron.BIAS, data.min_Input, data.max_Input, data.min_Output, data.max_Output);
            GNUPLOT(PAR.nameFileGnuplot, PAR.way_to_DataGnuplot, data.vectorOutputNorm, vector_Output_ANN, PAR.plot_1, PAR.plot_3);
            GNUPLOT(PAR.nameFileGnuplot, PAR.way_to_DataGnuplot, data.vectorOutputNorm, vector_Output_ANN, PAR.plot_2, PAR.plot_4);
        }
        std::cout << "epochs=" << f << " Error=" << Error_AVERAGE << std::endl;
        //запись весов и смещений в файл если текущая ошибка меньше предыдущей
        if (write_error > Error_AVERAGE)
        {
            write_error = Error_AVERAGE;
            write_Weight_and_Bias(perceptron.WEIGHT, perceptron.BIAS, data.min_Input, data.max_Input, data.min_Output, data.max_Output);
        }

        Error_AVERAGE = 0.00;
    }

    std::cout << "Min_epochs=" << min_epoch << " Min_Error=" << Min_Error << std::endl;
    std::cout << "Hello World!\n";
}// NEURAL_NETWORK.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.