#ifndef SYMBOL_H_
#define SYMBOL_H_

#include"HW_2.h"

class Symbol
{
private:
	int iSymbol;
	float fProb;
	int iSymbolCount;

public:
	Symbol();
	Symbol(int iSymbol, float fProb);
	void SetSymbol(int iSymbol);
	void SetProbability(float fProb);
	int GetSymbol();
	float GetProbability();
	void IncrementSymbolCount(){ this->iSymbolCount++; }
	int GetSymbolCount(){ return this->iSymbolCount; }
};

#endif // !SYMBOL_H_