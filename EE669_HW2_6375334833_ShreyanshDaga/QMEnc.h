#ifndef QMENC_H_H
#define QMENC_H_H

#include "HW_2.h"
#include "QMTableEntry.h"

class QMEnc
{
	private:
		unsigned int A;
		unsigned int C;
		int iCurrState;
		unsigned int Qe;
		bool bCarry, bLPS, bMPS;
		//QMTableEntry QMTable[45];
		vector<QMTableEntry*> QMTable;

	public:
		QMEnc();
		void LoadQMTable(string strTableFile);
};

#endif