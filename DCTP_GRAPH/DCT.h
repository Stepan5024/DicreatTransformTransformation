#pragma once

#include <vector>

class DCT
{
private:
	static float theta(int xi);
public:
	static const float PI;
	static std::vector<float>  dct(std::vector<float>& input_values);
	static std::vector<float> idct(std::vector<float>& input_values);
	static void compress(std::vector<float>& input_values, float percent);
};

