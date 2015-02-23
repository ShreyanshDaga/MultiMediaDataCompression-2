#include "HW_2.h"
#include "FileIO.h"

FileIO::FileIO()
{
	this->fp = NULL;
	this->iRByte = 0;
	this->iRp = 0;
	this->iRs = 0;
	this->iWByte = 0;
	this->iWs = 0;	
}

FileIO::FileIO(string strFileName, bool bMode)
{
	this->strFileName = strFileName;
	this->bMode = bMode;

	if (bMode)
		this->fp = fopen(strFileName.c_str(), "wb");
	else
	{ 
		// File Size
		this->fp = fopen(strFileName.c_str(), "rb");
		fseek(this->fp, 0, SEEK_END);
		this->iFileSize = ftell(this->fp);
		fseek(this->fp, 0, SEEK_SET);

		// Allocate Memory for File Contents
		this->fileBuffer = new char[this->iFileSize];

		// ReadFile in buffer
		fread(this->fileBuffer, sizeof(char), this->iFileSize, this->fp);

		// Close the file
		fclose(this->fp);
	}
}

bool FileIO::ReadBitFromFile()
{
	if (!bMode)
	{
		if (this->iRs == 0)
		{
			// Get the most recent byte 
			this->iRByte = this->fileBuffer[this->iRp];
			this->iRp++;
			this->iRs = 8;
		}

		bool bBit = (this->iRByte >> (this->iRs - 1)) & 1;;
		this->iRs--;

		return bBit;
	}
}

unsigned int FileIO::ReadByteFromFile()
{
	if (!bMode)
	{

	}
}

void FileIO::WriteBitToFile(bool bBit)
{

}

void FileIO::WriteByteToFile(unsigned int uByte)
{
	if (bMode)
	{

	}
}

void FileIO::WriteCodeToFile(string strCode)
{

}

bool FileIO::IsEOF()
{
	if (this->iRp == this->iFileSize && this->iRs == 0)
		return true;
	else
		return false;
}