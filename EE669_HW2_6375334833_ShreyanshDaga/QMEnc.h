#ifndef QMENC_H_H
#define QMENC_H_H

#include "HW_2.h"
#include "QMTableEntry.h"
#include "FileIO.h"

class QMEnc
{
	private:
		FileIO *pfileIP;
		FileIO *pfileOP;
		unsigned int A;
		unsigned short int C;
		int iCurrState;
		unsigned int Qe;
		bool bCarry, bLPS, bMPS;		
		vector<QMTableEntry*> QMTable;

	public:
		QMEnc();
		void LoadQMTable(string strTableFile);
		void Encode(string strIPFileName, bool bPre);
		void ReNormalize();
		void ChangeQe(bool bSymbol);
};

#endif