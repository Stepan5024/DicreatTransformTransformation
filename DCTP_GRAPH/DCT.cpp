#include "DCT.h"

const float DCT::PI = 3.14159265f;

float DCT::theta(int xi)
{
    return ((xi == 0) ? (1.0f / sqrt(2)) : 1.0f);
}

std::vector<float> DCT::dct(std::vector<float>& input_values)
{
    std::vector<float> dct_values;

    float n = (float)input_values.size();

    for (size_t u = 0; u < n; u++)
    {
        float i_th_value = sqrt(2.0f / n);
        float sum = 0;
        for (size_t i = 0; i < n; i++)
        {
            float res = theta(u);
            res *= cos(((PI * (float)u) / (2.0f * n)) * (2.0f * (float)i + 1.0f));
            res *= input_values[i];
            sum += res;
        }
        i_th_value *= sum;
        dct_values.push_back(i_th_value);
    }

    return dct_values;
}

std::vector<float> DCT::idct(std::vector<float>& input_values)
{
    std::vector<float> idct_values;

    float n = (float)input_values.size();

    for (size_t i = 0; i < n; i++)
    {
        float i_th_value = sqrt(2.0f / n);
        float sum = 0;
        for (size_t u = 0; u < n; u++)
        {
            float res = theta(u);
            res *= cos(((PI * (float)u) / (2.0f * n)) * (2.0f * (float)i + 1.0f));
            res *= input_values[u];
            sum += res;
        }
        i_th_value *= sum;
        idct_values.push_back(i_th_value);
    }

    return idct_values;
}

void DCT::compress(std::vector<float>& input_values, float percent)
{
    //float min_v = input_values[0], max_v = input_values[0];
    float sum = 0.f;
    for (auto &i : input_values)
    {
        //min_v = std::min(min_v, i);
        //max_v = std::max(max_v, i);
        sum += std::abs(i);
    }

    sum /= input_values.size();

    float treshold = sum * percent;
    
    for (size_t i = 0; i < input_values.size(); i++)
    {
        if (std::abs(input_values[i]) < treshold) 
        {
            input_values[i] = 0;
        }
    }
}
