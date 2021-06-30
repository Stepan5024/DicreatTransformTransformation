#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

const double PI = 4 * atan(1);
const short N = 48;
FILE* FileOut;

double cu(char xi);
vector<double> dctVal(vector<double>&);
vector<double> idctVal(vector<double>&);
void print(string);


int main()
{
    setlocale(LC_ALL, "Russian");
    system("color F0");

    vector<double> val;
    vector<double> dct;
    vector<double> idct;
    vector<double> valNoise;
    vector<double> valDCTNoise;
    vector<double> valIDCTNoise;
    vector<double> valSum;
    vector<double> valFilterDCT;
    vector<double> valDCTSum;
    vector<double> valIDCTFilterd;

    FileOut = fopen("file.txt", "w");

    fprintf(FileOut, "Дискретное косинусное преобразование 2-ого типа\n");

    for (short k = 0; k < N; k ++) val.push_back(sin(2 * PI * k / N));
    
    dct = dctVal(val);
    idct = idctVal(dct);

    fprintf(FileOut, "---------------------------------------------------------------------------------------------------\n");
    fprintf(FileOut, "К |    Полезный сигнал   |         ДКП-2        |          ОДКП-2      |  Ошибка восстановления  |\n");
    fprintf(FileOut, "--|----------------------|----------------------|----------------------|-------------------------|\n");

    for (short i = 0; i < N; i++) 
    {
        fprintf(FileOut, "%2d", i);
        fprintf(FileOut, "|%22.18f", val[i]);
        fprintf(FileOut, "|%22.18f", dct[i]);
        fprintf(FileOut, "|%22.18f", idct[i]);
        fprintf(FileOut, "|%25.18f|", fabs((idct[i] - val[i])));
        fprintf(FileOut, "\n");
    }

    for (short i = 0; i < N; i ++) valNoise.push_back(cos(20 * PI  * i / N));
    for (short i = 0; i < N; i++) valSum.push_back(val[i] + valNoise[i]);

    fprintf(FileOut, "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(FileOut, "U |    Полезный сигнал   |Значение шумного сигнала:|Значение суммы шума и сигнала:|        ДТК-2 помехи:    | ДТК-2 сигнала с помехой |Сигнал, отфильтрованный ОДКП-2|  Ошибка восстановления: |\n");
    fprintf(FileOut, "--|----------------------|-------------------------|------------------------------|-------------------------|-------------------------|------------------------------|-------------------------|\n");

    valDCTSum = dctVal(valSum);
    valDCTNoise = dctVal(valNoise);
    for (short i = 0; i < N; i++) valFilterDCT.push_back(valDCTSum[i] - valDCTNoise[i]);

    valIDCTFilterd = idctVal(valFilterDCT);

    for (short i = 0; i < N; i++) {
        fprintf(FileOut, "%2d", i);
        // полезный сигнал
        fprintf(FileOut, "|%22.18f", val[i]);
        //сигнал шума
        fprintf(FileOut, "|%25.18f", valNoise[i]);
        
        //сигнал суммы шума и полезной
        fprintf(FileOut, "|%30.18f", valSum[i]);

        //ДТК-2 шума
        fprintf(FileOut, "|%25.18f", valDCTNoise[i]);
     
        //ДТК-2 сумма шума и полезной
        fprintf(FileOut, "|%25.18f", valDCTSum[i]);
        
        //Отфильтрованный
        fprintf(FileOut, "|%30.18f", valIDCTFilterd[i]);
        //Ошибка преобразования
        fprintf(FileOut, "|%25.18f|", valIDCTFilterd[i] - val[i]);

        fprintf(FileOut, "\n");
    }
 
    fclose(FileOut);

    string line;
    ifstream in("file.txt");
    if (in.is_open())
    {
        while (getline(in, line))
        {
            cout << line << endl;
        }
    }
    in.close(); 
    return 0;
}

double cu( char xi)
{
    if (xi == 0) return sqrt(2.0) * 0.5;
    else return 1;
}

vector<double> dctVal(vector<double>& input_values)
{
    vector<double> dct_values;

    for (short u = 0; u < N; u++)
    {
        double u_th_value = sqrt(2.0 / N);
        u_th_value *= cu(u);
        double sum = 0;
        for (short k = 0; k < N; k++)
        {
            double res = cos((PI * u * (k + 0.5)) / N);
            res *= input_values[k];
            sum += res;
        }
        u_th_value *= sum;
        dct_values.push_back(u_th_value);
    }

    return dct_values;
}

vector<double> idctVal(vector<double>& input_values)
{
    vector<double> idct_values;

    for (short k = 0; k < N; k++)
    {
        double i_th_value = sqrt(2.0 / N);
        double sum = 0;
        for (short u = 0; u < N; u++)
        {
            double res = cu(u);
            res *= cos((PI * u * (k + 0.5)) / N);
            res *= input_values[u];
            sum += res;
        }
        i_th_value *= sum;
        idct_values.push_back(i_th_value);
    }

    return idct_values;
}


