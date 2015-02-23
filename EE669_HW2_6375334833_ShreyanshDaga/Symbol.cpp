#include"HW_2.h"
#include"Symbol.h"

Symbol::Symbol()
{
	this->iSymbol = 0;
	this->fProb = 0.00f;
	this->iSymbolCount = 0;
}
Symbol::Symbol(int iSymbol, float fProb)
{
	this->iSymbol = iSymbol;
	this->fProb = fProb;
	this->iSymbolCount = 0;
}
void Symbol::SetSymbol(int iSymbol)
{
	this->iSymbol = iSymbol;
}
void Symbol::SetProbability(float fProb)
{
	this->fProb = fProb;
}
int Symbol::GetSymbol()
{
	return this->iSymbol;
}
float Symbol::GetProbability()
{
	return this->fProb;
}