#include "HW_2.h"
#include "FileIO.h"

int** ComputeDCT(int **iaQN);

void Problem_3_A()
{
	// DCT and Quantization
	FileIO lena("lena.raw", false);

	int iaBlock[16][16];

	// Subtract 128 from original image
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			iaBlock[i][j] =((int)lena.fileBuffer[i * 16 + j]) - 128;
		}
	}

	// Init Q50 matrix
	int iaQ50[8][8] =	{
							{16,11,10,16,24,40,51,61},
							{12,12,14,19,26,58,60,55},
							{14,12,16,24,40,57,69,56},
							{14,17,22,29,51,87,80,62},
							{18,22,37,56,68,109,103,77},
							{24,35,55,64,81,104,113,92},
							{49,64,78,87,103,121,120,101},
							{72,92,95,98,112,100,103,99}							
						};
	int **piaQ50 = new int*[8];
	for (int i = 0; i < 8; i++)
		piaQ50[i] = new int[8];

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			piaQ50[i][j] = iaQ50[i][j];

	// Compute DCT for each 8x8 block
	int **piaDCTBlock = ComputeDCT(iaBlock);		//O/P = 16x16

	// Quantize the block
	int **piaQuantizedBlock50 = Quantize(piaDCTBlock, piaQ50);	// O/P = 16x16

	// Generate Q10, Q90
	int **piaQ10, **piaQ90;
	piaQ10 = ComputeQBlock(piaQ50, 10);
	piaQ90 = ComputeQBlock(piaQ50, 90);

	// Quantize with new block
	int **piaQuantizedBlock10, **piaQuantizedBlock90;
	piaQuantizedBlock10 = Quantize(piaDCTBlock, piaQ10);
	piaQuantizedBlock90 = Quantize(piaDCTBlock, piaQ90);

	// Write Results
	// DCT Coeff
	FileIO fileDCT("dct_coeff.txt", true);

	// Q50
	FileIO fileQ50("Q_50.txt", true);

	// Q10
	FileIO fileQ10("Q_10.txt", true);

	// Q90
	FileIO fileQ90("Q_90.txt", true);

	// O/P for Q50

	// O/P for Q10

	// O/P for Q90
	
}

void Problem_3_B()
{
	// Compression Quality Factor

}

void Problem_3_C()
{
	// Post-Processing of JPWG images
}

int** ComputeDCT(int iaBlock[16][16])
{

}

int** ComputeQBlock(int **piaQ50, int iN)
{

}

int** Quantize(int **piaBlock, int **piaQN)
{

}