#ifndef FILEIO_H_H
#define FILEIO_H_H

#include "HW_2.h"

class FileIO
{
	private:		
		FILE *fp;
		bool bMode;
		//char *fileBuffer;
		int iFileSize;
		unsigned int iRs, iRByte, iRp;
		unsigned int iWs, iWByte;

	public:
		unsigned char *fileBuffer;
		string strFileName;
		FileIO();
		FileIO(string strFileName, bool bMode);
		bool ReadBitFromFile();
		unsigned int ReadByteFromFile();
		void WriteBitToFile(bool bBit);
		void WriteByteToFile(unsigned int uByte);
		void WriteLastByte();
		void WriteCodeToFile(string strCode);
		bool IsEOF();
		void CloseFile();
		int GetFileSize();
		void PreProcessFile();
};

#endif // !FILEIO_H_H
