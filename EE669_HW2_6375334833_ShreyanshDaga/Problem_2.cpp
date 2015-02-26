#include "HW_2.h"
#include "LMaxSQ.h"

void Problem_2_A()
{
	// Scalar Quantization - Lloyd Max Quantizer
	LMaxSQ SQ;

	string	strTrainNames[3] = {"chem.256","house.256","couple.256"};

	SQ.SetTrainingImages(strTrainNames, 3, 3);
	SQ.TrainImgaes();

	// First Image
	SQ.Quantize("moon.256");
}

void Problem_2_B()
{
	// Vector Quantization
}