#include "HW_2.h"
#include "QMTableEntry.h"

QMTableEntry::QMTableEntry()
{
	this->iState = 0;
	this->iDecS = 0;
	this->iIncS = 0;
	this->Qe = 0;
}

QMTableEntry::QMTableEntry(int iState, unsigned int Qe, int iDecS, int iIncS)
{	
	this->iState = iState;
	this->iDecS = iDecS;
	this->iIncS = iIncS;
	this->Qe = Qe;
}

void QMTableEntry::SetIncS(int iIncS)
{

}

void QMTableEntry::SetDecS(int iDecS)
{

}

void QMTableEntry::SetQe(unsigned int Qe)
{

}

void QMTableEntry::SetState(int iState)
{

}

int QMTableEntry::GetState()
{
	return this->iState;
}

unsigned int QMTableEntry::GetQe()
{
	return this->Qe;
}

int QMTableEntry::GetIncS()
{
	return this->iIncS;
}

int QMTableEntry::GetDecS()
{
	return this->iDecS;
}