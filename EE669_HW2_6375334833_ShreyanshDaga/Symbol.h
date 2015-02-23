#ifndef SYMBOL_H_
#define SYMBOL_H_

#include"HW_2.h"

class Symbol
{
private:
	int iSymbol;
	float fProb;

public:
	Symbol();
	Symbol(int iSymbol, float fProb);
	void SetSymbol(int iSymbol);
	void SetProbability(float fProb);
	int GetSymbol();
	float GetProbability();
};

#endif // !SYMBOL_H_