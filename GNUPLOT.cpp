#include "Header.h"
#include "parametrs.h"

//using namespace::std;

//рисование графиков
double GNUPLOT(
    std::string nameFileGnuplot,
    std::string wayToFile,
    std::vector<std::vector<double>>& vector_Output,
    std::vector<std::vector<double>>& vector_Output_ANN,
    std::string graph1,
    std::string graph2)
{
    //std::string nameFileGnuplot{ "DataGnuplot.txt" };
    //std::string wayToFile{ "D:\\PROGRAMMS_C++\\ANN\\ANN\\" };

    std::string way{ wayToFile + nameFileGnuplot };  //путь до файла + название файла с которого будут строится графики

    std::string message{ "plot '" + way + "' using " + graph1 + " title 'MD' with lines linecolor 1,'" + way + "' using " + graph2 + " title 'MODEL' with lines linecolor 5\n" };
    std::string wayToGnuplot{ "C:\\gnuplot\\bin\\gnuplot.exe" }; //путь до исполняемого файла гнуплот
    const char* WAY_TO_DATA = message.c_str();  // преобразуем в указатель сообщение которое пойдет в консоль гнуплота 
    const char* WAY_TO_GNUPLOT = wayToGnuplot.c_str();


    FILE* pipe = _popen(WAY_TO_GNUPLOT, "w");
    if (pipe != NULL)
    {
        std::ofstream DATAGNUPLOT;

        DATAGNUPLOT.open(nameFileGnuplot);

        for (int i = 0; i < vector_Output.size(); i++)
        {
            DATAGNUPLOT << i << " ";
            for (int j = 0; j < vector_Output[0].size(); j++)
            {
                DATAGNUPLOT << vector_Output[i][j] << " ";
            }
            for (int j = 0; j < vector_Output_ANN[0].size(); j++)
            {
                DATAGNUPLOT << vector_Output_ANN[i][j] << " ";
            }
            DATAGNUPLOT << std::endl;
        }
        DATAGNUPLOT.close();
        fprintf(pipe, WAY_TO_DATA);

        fflush(pipe);

        // ожидание нажатия клавиши
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();

#ifdef WIN32
        _pclose(pipe);
#else
        _pclose(pipe);
#endif
    }
    else puts("Could not open the file\n");
    //getchar();
    _pclose(pipe);
    return 0;
}
