#ifndef QMTABLENTRY_H_
#define QMTABLENTRY_H_

#include "HW_2.h"

class QMTableEntry
{
	private:
		int iState;
		unsigned int Qe;
		int iIncS;
		int iDecS;	
	
	public:
		QMTableEntry();
		QMTableEntry(int iState, unsigned int Qe, int iDecS, int iIncS);
		void SetIncS(int iIncS);
		void SetDecS(int iDecS);
		void SetQe(unsigned int Qe);
		void SetState(int iState);
		int GetState();
		unsigned int GetQe();
		int GetIncS();
		int GetDecS();
};

#endif // !QMTABLENTRY_H_