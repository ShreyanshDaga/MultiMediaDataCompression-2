#include "HW_2.h"
#include "FileIO.h"

void Deblock_1(FileIO *pJFile, FileIO *pOriginal, bool bColor);
void Deblock_2(FileIO *pJFile, FileIO *pOriginal, bool bColor);
void Deblock_3(FileIO *pJFile, FileIO *pOriginal, bool bColor);
void DeBlock_1_Matrix(FileIO *pJFile, FileIO *pOriginal, bool bColor);

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
	FileIO *pPeppers[5], *pClock[5];
	FileIO fPepper("pepper.raw", false);
	//FileIO fClock("clock.raw", false);
	FileIO fTest("RAW_Q3\\pepper1.raw", false);

	//Deblock_1(&fTest, &fPepper, true);
	DeBlock_1_Matrix(&fTest, &fPepper, true);

	//Read Peppers and Clocl Raw Images
	for (int i = 0; i < 5; i++)
	{
		char strPeppers[30];
		char strClocks[30];
		
		sprintf(strPeppers, "RAW_Q3\\pepper%d.raw", i + 1);
		sprintf(strClocks, "RAW_Q3\\clock%d.raw", i + 1);						

		pPeppers[i] = new FileIO(strPeppers, false);
		//pClock[i] = new FileIO(strClocks, false);		
	}

	// Deblock Method 1
	for (int i = 0; i < 5; i++)
	{		
		Deblock_1(pPeppers[i], &fPepper, true);
		//Deblock_1(pClock[i], &fClock, false);

		Deblock_2(pPeppers[i], &fPepper, true);
		//Deblock_2(pClock[i], &fClock, false);

		Deblock_3(pPeppers[i], &fPepper, true);
		//Deblock_3(pClock[i], &fClock, false);

	}
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

float GetPSNR(unsigned char *pComp, unsigned char *pOriginal, int iFileSize)
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

void Deblock_1(FileIO *pJFile, FileIO *pOriginal, bool bColor)
{
	string strOPFileName = GenerateOpFileName(pJFile->strFileName, "_q3c_op.raw");
	// Low Pass Filter
	int iSize, iBPP;
	int iN;

	if (bColor)
		iBPP = 3;
	else
		iBPP = 1;

	iN = sqrt(pOriginal->GetFileSize() / iBPP);

	unsigned char **pOriginalImageR = new unsigned char*[iN];
	unsigned char **pOriginalImageG = new unsigned char*[iN];
	unsigned char **pOriginalImageB = new unsigned char*[iN];
	unsigned char **pJImageR = new unsigned char*[iN + 2];
	unsigned char **pJImageG = new unsigned char*[iN + 2];
	unsigned char **pJImageB = new unsigned char*[iN + 2];

	unsigned char cImageR[256][256][3];
	unsigned char cJImageR[258][258][3];

	FileIO fOutput(strOPFileName.c_str(), true);

	for (int i = 0; i < iN; i++)
	{
		pOriginalImageR[i] = new unsigned char[iN];		
		pOriginalImageG[i] = new unsigned char[iN];
		pOriginalImageB[i] = new unsigned char[iN];
		pJImageR[i] = new unsigned char[iN + 2];
		pJImageG[i] = new unsigned char[iN + 2];
		pJImageB[i] = new unsigned char[iN + 2];		
	}
	pJImageR[iN] = new unsigned char[iN + 2];
	pJImageR[iN + 1] = new unsigned char[iN + 2];
	pJImageG[iN] = new unsigned char[iN + 2];
	pJImageG[iN + 1] = new unsigned char[iN + 2];
	pJImageB[iN] = new unsigned char[iN + 2];
	pJImageB[iN + 1] = new unsigned char[iN + 2];
	
	for (int i = 0; i < iN +2; i++)
	{
		for (int j = 0; j < iN + 2; j++)
		{			
				pJImageR[i][j] = 0;
				pJImageG[i][j] = 0;
				pJImageB[i][j] = 0;		
		}
	}

	int p = 0;
	for (int i = 0; i < iN; i++)
	{
		for (int j = 0; j < iN; j++)
		{						
			if (bColor)
			{
				pOriginalImageR[i][j] = (unsigned char)pOriginal->fileBuffer[i*iN + p];
				pOriginalImageG[i][j] = (unsigned char)pOriginal->fileBuffer[i*iN + p + 1];
				pOriginalImageB[i][j] = (unsigned char)pOriginal->fileBuffer[i*iN + p + 2];

				pJImageR[i + 1][j + 1] = (unsigned char)pJFile->fileBuffer[i*iN + p];
				pJImageG[i + 1][j + 1] = (unsigned char)pJFile->fileBuffer[i*iN + p + 1];
				pJImageB[i + 1][j + 1] = (unsigned char)pJFile->fileBuffer[i*iN + p + 2];
				p += 3;
			}
			else
			{
				pJImageR[i + 1][j + 1] = pJFile->fileBuffer[i*iN + j];
				pOriginalImageR[i][j] = pOriginal->fileBuffer[i*iN + j];
			}							
		}
	}	

	// LPF
	for (int i = 1; i < iN + 1; i++)
	{
		for (int j = 1; j < iN + 1; j++)
		{
			unsigned long iSumR = 0;
			unsigned long iSumG = 0;
			unsigned long iSumB = 0;

			for (int k = 2; k >= 0; k--)
			{
				for (int l = 2; l >= 0; l--)
				{
					
					if (bColor)
					{
						iSumR += pJImageR[i - k + 1][j - l + 1];
						iSumB += pJImageB[i - k + 1][j - l + 1];
						iSumG += pJImageG[i - k + 1][j - l + 1];
					}
					else
					{
						iSumR += pJImageR[i - k + 1][j - l + 1];
					}
				}
			}
			
			
			if (bColor)
			{
				unsigned char cResR = iSumR / 9;
				unsigned char cResG = iSumG / 9;
				unsigned char cResB = iSumB / 9;

				fOutput.WriteByteToFile(cResR);
				fOutput.WriteByteToFile(cResG);
				fOutput.WriteByteToFile(cResB);
			}
			else
			{
				unsigned char cResR = iSumR / 9;

				fOutput.WriteByteToFile(cResR);
			}
			//pResImage[i - 1][j - 1] = cRes;			
		}
	}
	fOutput.CloseFile();

	// Calculate PSNR

	
}

void Deblock_2(FileIO *pJFile, FileIO *pOriginal, bool bColor)
{
	// If color, convert back from YUV

	// If color, convert to YUV

	// DeBlock H

	// DeBlock V
}

void Deblock_3(FileIO *pJFile, FileIO *pOriginal, bool bColor)
{

}

void DeBlock_1_Matrix(FileIO *pJFile, FileIO *pOriginal, bool bColor)
{
	string strOPFileName;

	unsigned char cImageR[256][256][3];
	unsigned char cJImageR[258][258][3];	

	FileIO fOutput("test_output.raw", true);
	FILE *fp = fopen("testtest.raw", "w");

	for (int i = 0; i < 258; i++)
	{
		for (int j = 0; j < 258; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				cJImageR[i][j][k] = 128;
			}
		}
	}

	for (int i = 0; i < 256; i++)
		for (int j = 0; j < 256; j++)
			for (int k = 0; k < 3; k++)
				cJImageR[i + 1][j + 1][k] = pJFile->fileBuffer[i * 256 + j * 3 + k];


	for (int i = 1; i < 256 + 1; i++)
	{
		for (int j = 1; j < 256 + 1; j++)
		{
			unsigned long iSumR = 0;
			unsigned long iSumG = 0;
			unsigned long iSumB = 0;

			for (int k = 2; k >= 0; k--)
			{
				for (int l = 2; l >= 0; l--)
				{

					if (bColor)
					{
						iSumR += cJImageR[i - k + 1][j - l + 1][0];
						iSumB += cJImageR[i - k + 1][j - l + 1][1];
						iSumG += cJImageR[i - k + 1][j - l + 1][2];
					}
					else
					{
						iSumR += cJImageR[i - k + 1][j - l + 1][0];
					}
				}
			}

			if (bColor)
			{
				unsigned char cResR = iSumR / 9;
				unsigned char cResG = iSumG / 9;
				unsigned char cResB = iSumB / 9;

				fOutput.WriteByteToFile(cResR);
				fOutput.WriteByteToFile(cResG);
				fOutput.WriteByteToFile(cResB);

				fputc(cResR, fp);
				fputc(cResG, fp);
				fputc(cResB, fp);
			}
			else
			{
				unsigned char cResR = iSumR / 9;

				fOutput.WriteByteToFile(cResR);
			}
		}
	}

	fOutput.CloseFile();
	fclose(fp);
}