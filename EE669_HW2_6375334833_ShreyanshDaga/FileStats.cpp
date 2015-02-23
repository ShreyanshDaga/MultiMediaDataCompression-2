#include"HW_2.h"
#include"FileStats.h"

FileStats::FileStats()
{
	// Default ctor
}

FileStats::FileStats(string strFileName)
{
	this->strFileName = strFileName;
	this->bStats = false;
	this->iFileSize = 0;
	
	this->GenerateFileStats();
}

void FileStats::GenerateFileStats()
{
	// Open the file
	this->fp = fopen(this->strFileName.c_str(), "rb");
	/// Exception

	// File Size
	fseek(this->fp, 0, SEEK_END);
	this->iFileSize = ftell(this->fp);
	fseek(this->fp, 0, SEEK_SET);

	// Init SymbolTable for 0 and 1
	this->symTable[0].SetSymbol(0);
	this->symTable[0].SetProbability(0.00f);
	this->symTable[1].SetSymbol(1);
	this->symTable[1].SetProbability(0.00f);

	// Read each byte and count bits
	for (int i = 0; i < this->iFileSize; i++)
	{
		unsigned int uByte = (unsigned int)fgetc(this->fp);
		for (int j = 0; j < 8; j++)
		{
			int bBit = 0x01 && (uByte >> j);
			this->symTable[bBit].IncrementSymbolCount();
		}
	}

	// Calculate Probability
	float fProb;
	fProb = ((float) (this->symTable[0].GetSymbolCount())) / (float)(this->iFileSize);
	this->symTable[0].SetProbability(fProb);
	fProb = ((float)(this->symTable[1].GetSymbolCount())) / (float)(this->iFileSize);
	this->symTable[1].SetProbability(fProb);

	// Calculate Entropy
	this->fEntropy = 0.00f;
	this->fEntropy += this->symTable[0].GetProbability()*log10f(this->symTable[0].GetProbability()) / log10f(2.00f);
	this->fEntropy += this->symTable[1].GetProbability()*log10f(this->symTable[1].GetProbability()) / log10f(2.00f);
	this->fEntropy *= -1.00f;

	// Stats Computed, close the file
	fclose(this->fp);
	this->bStats = true;
}

string FileStats::GetFileName()
{
	return this->strFileName;
}

int FileStats::GetFileSize()
{
	if (this->bStats)
		return this->iFileSize;
	else
	{
		this->GenerateFileStats();
		return this->iFileSize;
	}
}

float FileStats::GetEntropy()
{
	if (this->bStats)
		return this->iFileSize;
	else
	{
		this->GenerateFileStats();
		return this->fEntropy;
	}
}

void FileStats::SetFileName(string strFileName)
{
	if (!this->bStats)
	{
		this->strFileName = strFileName;
	}	
}

Symbol* FileStats::GetSymbolTable()
{
	if (this->bStats)
		return this->symTable;
	else
	{
		this->GenerateFileStats();
		return this->symTable;
	}
}

void FileStats::WriteFileStats()
{
	// OP file name
	string strOPFileName(this->strFileName);	
	int iPos = strOPFileName.find('.');
	string strOPFileName = strOPFileName.substr(0, iPos) + "_Stats.txt";
	
	// Open the file
	FILE *fp = fopen(strOPFileName.c_str(), "w");
	/// Handle Exception

	// Write Stats
	fprintf(fp, "Input File Name: %s", this->strFileName.c_str());
	fprintf(fp, "\nEntropy: %f", this->fEntropy);
	fprintf(fp, "\nTotal Symbols: %d", 2);
	fprintf(fp, "\n\nSymbol(Binary) : Relative Frequnecy");

	// For Symbol 0
	string szProb = to_string(this->symTable[0].GetProbability());	
	string szFinal = "\n0  : " + szProb;
	fprintf(fp, "%s", szFinal.c_str());

	// For Symbol 1
	szProb = to_string(this->symTable[1].GetProbability());
	szFinal = "\n0  : " + szProb;
	fprintf(fp, "%s", szFinal.c_str());

	// Close the file 
	fclose(fp);
}