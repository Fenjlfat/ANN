#pragma once

class FileHandling
{
public:
    int numberPoint{ 0 };
    int columnsFile;
    int inputData;
    int outputData;
    std::string nameFile;
    std::vector<std::vector<double>> vectorFile;      //������������� ������� ���� ����� �������� ������ � �����
    std::vector<std::vector<double>> vectorInput;     //������������� ������� ������� ��������
    std::vector<std::vector<double>> vectorOutput;    //������������� ������� �������� ��������
public:
    FileHandling(std::string name_File, int columns_File, int input_Data, int output_Data);
    ~FileHandling();
    void setFileHandling();

    int processingFile(); // ������������ ����
};

