#include "HW_2.h"
#include "FileIO.h"

int** ComputeDCT(int iaBlock[16][16]);
int** ComputeQBlock(int **piaQ50, int iN);
int** Quantize(int **piaBlock, int **piaQN);
float GetPSNR (char *pComp, char *pOriginal, int iFIleSize);

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
			iaBlock[i][j] =((unsigned char)lena.fileBuffer[i * 16 + j]) - 128;
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
	piaQuantizedBlock10 = Quantize(piaDCTBlock, piaQ10);	// O/P = 16x16
	piaQuantizedBlock90 = Quantize(piaDCTBlock, piaQ90);	// O/P = 16x16

	// Write Results
	// DCT Coeff	
	FILE *fp = fopen("dct_coeff.txt", "w");
	for (int i = 0; i < 16; i++)
	{ 
		for (int j = 0; j < 16; j++)
		{
			fprintf(fp, "%d\t", piaDCTBlock[i][j]);
		}
		fputc('\n', fp);
	}
	fclose(fp);

	// Q50, Q10, Q90	
	FILE *fp_50 = fopen("Q_50.txt", "w");
	FILE *fp_10 = fopen("Q_10.txt", "w");
	FILE *fp_90 = fopen("Q_90.txt", "w");
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			fprintf(fp_50, "%d\t", piaQ50[i][j]);
			fprintf(fp_10, "%d\t", piaQ10[i][j]);
			fprintf(fp_90, "%d\t", piaQ90[i][j]);
		}
		fputc('\n', fp_50);
		fputc('\n', fp_10);
		fputc('\n', fp_90);
	}
	fclose(fp_50);
	fclose(fp_10);
	fclose(fp_90);	

	// O/P for Q50, Q10, Q90
	FILE *fp_Op_50 = fopen("Op_50.txt", "w");
	FILE *fp_Op_10 = fopen("Op_10.txt", "w");
	FILE *fp_Op_90 = fopen("Op_90.txt", "w");
	
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			fprintf(fp_Op_50, "%d\t", piaQuantizedBlock50[i][j]);
			fprintf(fp_Op_10, "%d\t", piaQuantizedBlock10[i][j]);
			fprintf(fp_Op_90, "%d\t", piaQuantizedBlock90[i][j]);
		}
		fputc('\n', fp_Op_50);
		fputc('\n', fp_Op_10);
		fputc('\n', fp_Op_90);
	}
	fclose(fp_Op_50);
	fclose(fp_Op_10);
	fclose(fp_Op_90);
}

void Problem_3_B()
{
	// Read All Images
	FileIO *pfiles[8];
	pfiles[0] = new FileIO("clock_q_1.raw", false);
	pfiles[1] = new FileIO("clock_q_5.raw", false);
	pfiles[2] = new FileIO("clock_q_10.raw", false);
	pfiles[3] = new FileIO("clock_q_20.raw", false);
	pfiles[4] = new FileIO("clock_q_40.raw", false);
	pfiles[5] = new FileIO("clock_q_60.raw", false);
	pfiles[6] = new FileIO("clock_q_80.raw", false);
	pfiles[7] = new FileIO("clock_q_100.raw", false);
	
	// Read Original
	FileIO file_original("clock.raw", false);

	// Compute Statistics
	float pfPSNR[8];

	for (int i = 0; i < 8; i++)
	{
		pfPSNR[i] = GetPSNR(pfiles[i]->fileBuffer, file_original.fileBuffer, file_original.GetFileSize());
		//cout << " " << pfPSNR[i];
	}

	// Write Statistics
	FILE *fp = fopen("Q3B_Results.txt", "w");

	fprintf(fp, "PSNR Results\n");
	fprintf(fp, "\nFile: clock_q_1.raw,    PSNR: %f", pfPSNR[0]);
	fprintf(fp, "\nFile: clock_q_5.raw,    PSNR: %f", pfPSNR[1]);
	fprintf(fp, "\nFile: clock_q_10.raw,   PSNR: %f", pfPSNR[2]);
	fprintf(fp, "\nFile: clock_q_20.raw,   PSNR: %f", pfPSNR[3]);
	fprintf(fp, "\nFile: clock_q_40.raw,   PSNR: %f", pfPSNR[4]);
	fprintf(fp, "\nFile: clock_q_60.raw,   PSNR: %f", pfPSNR[5]);
	fprintf(fp, "\nFile: clock_q_80.raw,   PSNR: %f", pfPSNR[6]);
	fprintf(fp, "\nFile: clock_q_100.raw,  PSNR: %f", pfPSNR[7]);

	fclose(fp);
}

void Problem_3_C()
{
	// Post-Processing of JPEG images

	// Get Raw Images

	// If color, convert to YUV

	// DeBlock H

	// DeBlock V

	// If color, convert back from YUV

	// Write O/p Image
}

int** ComputeDCT(int iaBlock[16][16])
{
	int ** pDCT = new int*[16];
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
			pDCT[i] = new int[16];


	float fU = 1;
	float fV = 1;

	// Block 1
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			pDCT[i][j] = 0;
			if (i == 0)
				fU = 0.707;
			else
				fU = 1.00;

			if (j == 0)
				fV = 0.707;
			else
				fV = 1.00;

			for (int x = 0; x < 8; x++)
			{
				for (int y = 0; y < 8; y++)
				{
					pDCT[i][j] += iaBlock[x][y] * cosf((2 * x + 1) * i * 3.14159 / (16)) * cosf((2 * y + 1) * j * 3.14159 / (16));
				}
			}

			pDCT[i][j] = pDCT[i][j] * 0.25 * fU * fV;
		}
	}

	// Block 2
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			pDCT[i][j+8] = 0;
			if (i == 0)
				fU = 0.707;
			else
				fU = 1.00;

			if (j == 0)
				fV = 0.707;
			else
				fV = 1.00;

			for (int x = 0; x < 8; x++)
			{
				for (int y = 0; y < 8; y++)
				{
					pDCT[i][j+8] += iaBlock[x][y+8] * cosf((2 * x + 1) * i * 3.14159 / (16)) * cosf((2 * y + 1) * j * 3.14159 / (16));
				}
			}

			pDCT[i][j+8] = pDCT[i][j+8] * 0.25 * fU * fV;
		}
	}

	// Block 3
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			pDCT[i+8][j] = 0;
			if (i == 0)
				fU = 0.707;
			else
				fU = 1.00;

			if (j == 0)
				fV = 0.707;
			else
				fV = 1.00;

			for (int x = 0; x < 8; x++)
			{
				for (int y = 0; y < 8; y++)
				{
					pDCT[i+8][j] += iaBlock[x+8][y] * cosf((2 * x + 1) * i * 3.14159 / (16)) * cosf((2 * y + 1) * j * 3.14159 / (16));
				}
			}

			pDCT[i+8][j] = pDCT[i+8][j] * 0.25 * fU * fV;
		}
	}

	// Block 4
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			pDCT[i+8][j+8] = 0;
			if (i == 0)
				fU = 0.707;
			else
				fU = 1.00;

			if (j == 0)
				fV = 0.707;
			else
				fV = 1.00;

			for (int x = 0; x < 8; x++)
			{
				for (int y = 0; y < 8; y++)
				{
					pDCT[i+8][j+8] += iaBlock[x+8][y+8] * cosf((2 * x + 1) * i * 3.14159 / (16)) * cosf((2 * y + 1) * j * 3.14159 / (16));
				}
			}

			pDCT[i+8][j+8] = pDCT[i+8][j+8] * 0.25 * fU * fV;
		}
	}

	// Return the DCT computed coefficients
	return pDCT;
}

int** ComputeQBlock(int **piaQ50, int iN)
{
	int **pQN = new int*[8];
	for (int i = 0; i < 8; i++)
		pQN[i] = new int[8];


	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (iN > 50)
				pQN[i][j] = ((float)(100 - iN)) / (float) 50 * piaQ50[i][j];
			else if (iN < 50)
				pQN[i][j] = ((float)50/iN) * piaQ50[i][j];
		}
	}

	return pQN;
}

int** Quantize(int **piaBlock, int **piaQN)
{
	int **pAns = new int*[16];
	for (int i = 0; i < 16; i++)
		pAns[i] = new int[16];

	// Block 1
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			pAns[i][j] = piaBlock[i][j] / piaQN[i][j];

	// Block 2
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			pAns[i+8][j] = piaBlock[i+8][j] / piaQN[i][j];

	// Block 3
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			pAns[i][j+8] = piaBlock[i][j+8] / piaQN[i][j];

	// Block 4
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			pAns[i+8][j+8] = piaBlock[i+8][j+8] / piaQN[i][j];

	return pAns;
}

float GetPSNR(char *pComp, char *pOriginal, int iFileSize)
{	
	float fMSE = 0, fDiff, fPSNR;

	for (int i = 0; i < iFileSize; i++)
	{
		unsigned char cComp = pComp[i];
		unsigned char cOrig = pOriginal[i];
		
		fDiff = pow((cComp - cOrig), 2);
		fMSE += fDiff;
	}

	fMSE /= iFileSize;

	fPSNR = 10 * log10f(pow(255, 2) / fMSE);

	return fPSNR;
}