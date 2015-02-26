#include "HW_2.h"
#include "FileStats.h"
#include "QMEnc.h"
#include "QMCODER.H"


void EncodeUsingCABAC(string strIpFileName, int iCtxSize);
int GetContext(bool * pCtxArray, int iCtxSize);
void ShiftBit(bool *pCtxArray, bool bBit, int iCtxSize);

void Problem_1_B()
{	
	// Simple BAC
	// File Statistics for Text file
	/*FileStats fText("text.dat");
	QMEnc enc;

	enc.LoadQMTable("QM_state_transition_table.txt");	
	enc.Encode("text.dat", false);*/

	/*FileStats fImage("image.dat");
	FileStats fBin("binary.dat");
	FileStats fAudio("audio.dat");*/

	// CABAC
	EncodeUsingCABAC("binary.dat", 1);
}

void EncodeUsingCABAC(string strIpFileName, int iCtxSize)
{
	// Read the input file
	bool *pCtxArray = new bool[iCtxSize];
	for (int i = 0; i < iCtxSize; i++) pCtxArray[i] = false;

	FileIO file(strIpFileName.c_str(), false);
	FILE *fpOut = fopen("cabacout.dat", "w+");

	QM Enc(fpOut);

	Enc.StartQM("encode");

	while (!file.IsEOF())
	{		
		if (file.ReadBitFromFile() == false)	// 0
		{
			int iCtx = GetContext(pCtxArray, iCtxSize);
			Enc.encode(0, iCtx);
			ShiftBit(pCtxArray, 0, iCtxSize);
		}
		else									// 1
		{								
			int iCtx = GetContext(pCtxArray, iCtxSize);
			Enc.encode(1, iCtx);
			ShiftBit(pCtxArray, 1, iCtxSize);
		}				
	}

	Enc.Flush();
	fclose(fpOut);
}

int GetContext(bool * pCtxArray, int iCtxSize)
{
	int iCtx = 0;
	for (int i = 0; i < iCtxSize; i++)
	{
		iCtx += pow(2, i) * pCtxArray[i];
	}

	return iCtx;
}

void ShiftBit(bool *pCtxArray, bool bBit, int iCtxSize)
{
	for (int i = iCtxSize - 1; i >= 0; i--)
	{
		if (i == 0)
		{
			pCtxArray[i] = bBit;
		}
		else
		{
			pCtxArray[i] = pCtxArray[i - 1];
		}
	}
}