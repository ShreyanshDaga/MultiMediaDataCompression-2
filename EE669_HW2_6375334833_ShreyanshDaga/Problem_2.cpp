#include "HW_2.h"
#include "LMaxSQ.h"

void Problem_2_A()
{
	// Scalar Quantization - Lloyd Max Quantizer
	LMaxSQ SQ;

	string	strTrainNames[3] = {"chem.256","house.256","couple.256"};

	SQ.SetTrainingImages(strTrainNames, 3, 5);
	SQ.TrainImgaes();
	
	SQ.Quantize("chem.256");
	SQ.Quantize("house.256");
	SQ.Quantize("couple.256");

	SQ.Quantize("f16.256");
	SQ.Quantize("elaine.256");
	SQ.Quantize("moon.256");	
}

void Problem_2_B()
{
	// Image Blocking

}
