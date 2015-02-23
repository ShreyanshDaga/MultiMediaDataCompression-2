#ifndef FILESTATS_H_
#define FILESTATS_H_

#include"HW_2.h"
#include"Symbol.h"

class FileStats
{
private:
	string strFileName;
	int iFileSize;
	FILE *fp;
	float fEntropy;
	bool bStats;	
	Symbol symTable[2];				// For only 2 symbols 0 and 1

public:
	FileStats();
	FileStats(string strFileName);
	void GenerateFileStats();
	string GetFileName();
	int GetFileSize();
	float GetRntropy();
	void SetFileName(string strFileName);
	Symbol* GetSymbolTable();
};

#endif