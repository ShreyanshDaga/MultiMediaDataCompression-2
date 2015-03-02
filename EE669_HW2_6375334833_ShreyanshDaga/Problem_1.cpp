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
	FileStats fText("text.dat");
	QMEnc enc;
	enc.LoadQMTable("QM_state_transition_table.txt");	
	
	enc.Encode("text.dat", false);
	enc.Encode("audio.dat", false);
	enc.Encode("binary.dat", false);
	enc.Encode("image.dat", false);

	enc.Encode("text_H_Comp.dat", false);
	enc.Encode("audio_H_Comp.dat", false);
	enc.Encode("binary_H_Comp.dat", false);
	enc.Encode("image_H_Comp.dat", false);

	// CABAC
	EncodeUsingCABAC("image.dat", 1);
	EncodeUsingCABAC("image.dat", 2);
	EncodeUsingCABAC("image.dat", 3);
	EncodeUsingCABAC("image.dat", 4);

	EncodeUsingCABAC("text.dat", 1);
	EncodeUsingCABAC("text.dat", 2);
	EncodeUsingCABAC("text.dat", 3);
	EncodeUsingCABAC("text.dat", 4);

	EncodeUsingCABAC("audio.dat", 1);
	EncodeUsingCABAC("audio.dat", 2);
	EncodeUsingCABAC("audio.dat", 3);
	EncodeUsingCABAC("audio.dat", 4);

	EncodeUsingCABAC("binary.dat", 1);
	EncodeUsingCABAC("binary.dat", 2);
	EncodeUsingCABAC("binary.dat", 3);
	EncodeUsingCABAC("binary.dat", 4);

	EncodeUsingCABAC("image_H_Comp.dat", 1);
	EncodeUsingCABAC("image_H_Comp.dat", 2);
	EncodeUsingCABAC("image_H_Comp.dat", 3);
	EncodeUsingCABAC("image_H_Comp.dat", 4);

	EncodeUsingCABAC("text_H_Comp.dat", 1);
	EncodeUsingCABAC("text_H_Comp.dat", 2);
	EncodeUsingCABAC("text_H_Comp.dat", 3);
	EncodeUsingCABAC("text_H_Comp.dat", 4);

	EncodeUsingCABAC("audio_H_Comp.dat", 1);
	EncodeUsingCABAC("audio_H_Comp.dat", 2);
	EncodeUsingCABAC("audio_H_Comp.dat", 3);
	EncodeUsingCABAC("audio_H_Comp.dat", 4);

	EncodeUsingCABAC("binary_H_Comp.dat", 1);
	EncodeUsingCABAC("binary_H_Comp.dat", 2);
	EncodeUsingCABAC("binary_H_Comp.dat", 3);
	EncodeUsingCABAC("binary_H_Comp.dat", 4);
}

void EncodeUsingCABAC(string strIpFileName, int iCtxSize)
{
	// Read the input file
	bool *pCtxArray = new bool[iCtxSize];
	for (int i = 0; i < iCtxSize; i++) pCtxArray[i] = false;

	FileIO file(strIpFileName.c_str(), false);
	char strName[30];
	sprintf(strName, "_CABAC_%d_OP.dat", iCtxSize);
	string strOPFileName = GenerateOpFileName(strIpFileName, strName);
	FILE *fpOut = fopen(strOPFileName.c_str(), "w+");

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