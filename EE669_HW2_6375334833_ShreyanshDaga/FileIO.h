#ifndef FILEIO_H_H
#define FILEIO_H_H

#include "HW_2.h"

class FileIO
{
	private:
		string strFileName;
		FILE *fp;
		bool bMode;
		char *fileBuffer;
		int iFileSize;
		unsigned int iRs, iRByte, iRp;
		unsigned int iWs, iWByte;

	public:
		FileIO();
		FileIO(string strFileName, bool bMode);
		bool ReadBitFromFile();
		unsigned int ReadByteFromFile();
		void WriteBitToFile(bool bBit);
		void WriteByteToFile(unsigned int uByte);
		void WriteCodeToFile(string strCode);
		bool IsEOF();
};

#endif // !FILEIO_H_H
