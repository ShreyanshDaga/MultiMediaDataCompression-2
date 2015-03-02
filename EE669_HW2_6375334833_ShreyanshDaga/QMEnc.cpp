#include "HW_2.h"
#include "QMEnc.h"

QMEnc::QMEnc()
{
	this->A = 0x10000;
	this->bCarry = false;
	this->C = 0;
	this->iCurrState = 10;
	this->Qe = 0x299A;
	this->bLPS = 1;
	this->bMPS = 0;
}

void QMEnc::LoadQMTable(string strTableFile)
{
	// Open Table file
	FILE *fp = fopen(strTableFile.c_str(), "r");
	/// Exception

	// Read file line by line
	char szLine[80];
	while (!feof(fp))
	{
		if (feof(fp))
			break;

		// Read the line
		fgets(szLine, 80, fp);

		// Break the string into parts and
		// Create QMTableEntry
		char *pEnd;
		int iState, iIncS, iDecS;
		unsigned int Qe;
		double dQe;

		iState = strtol(szLine, &pEnd, 10);
		Qe = strtol(pEnd, &pEnd, 16);
		dQe = strtod(pEnd, &pEnd);
		iIncS = strtol(pEnd, &pEnd, 10);
		iDecS = strtol(pEnd, NULL, 10);
		QMTableEntry *pQMEntry = new QMTableEntry(iState, Qe, iDecS, iIncS);
		// Add to QMTable
		this->QMTable.push_back(pQMEntry);		
	}	

	// Close the file
	fclose(fp);
}

void QMEnc::Encode(string strIPFileName, bool bPre)
{
	// FILEIO
	this->pfileIP = new FileIO(strIPFileName.c_str(), false);
	string strOpFileName = GenerateOpFileName(strIPFileName, "_BAC_op.dat");
	this->pfileOP = new FileIO(strOpFileName.c_str(), true);

	if (bPre)
		this->pfileIP->PreProcessFile();

	// QM Encoding algorithm
	while (!pfileIP->IsEOF())
	{
		if (pfileIP->ReadBitFromFile() == this->bMPS)
		{
			this->A -= this->Qe;
			if (this->A < 0x8000)
			{
				if (this->A < this->Qe)
				{
					if (this->C + this->A > 0xFFFF)
						this->bCarry = true;

					this->C += this->A;
					this->A = this->Qe;
				}

				this->ChangeQe(true);
				this->ReNormalize();
			}
		}
		else
		{
			// This is LPS
			this->A -= this->Qe;
			if (this->A >= this->Qe)
			{
				if (this->C + this->A > 0xFFFF)
					this->bCarry = true;

				this->C += this->A;
				this->A = this->Qe;
			}
			this->ChangeQe(false);
			this->ReNormalize();
		}
	}

	this->pfileOP->WriteLastByte();
	cout << "Op is generated";
}

void QMEnc::ReNormalize()
{
	if (this->bCarry)
	{
		this->pfileOP->WriteBitToFile(true);
		this->bCarry = false;
	}

	// Output until value of A >= 0x8000
	while (this->A < 0x8000)
	{
		this->A = this->A << 1;

		//if MSB = 0
		if ((this->C & 0x8000) == 0)
		{
			// Write 0
			this->pfileOP->WriteBitToFile(false);
		}
		else // if MSB = 1
		{
			// Write 1
			this->pfileOP->WriteBitToFile(true);
		}

		this->C = this->C << 1;
	}
}

void QMEnc::ChangeQe(bool bSymbol)
{
	// IF MPS is recvd increment state
	if (bSymbol)
	{
		int iTemp = this->QMTable[this->iCurrState]->GetIncS();
		this->iCurrState += iTemp;
	}
	else // IF LSP is recvd decrement state
	{
		int iTemp = this->QMTable[this->iCurrState]->GetDecS();
		this->iCurrState -= iTemp;

		// Swap MPS and LPS
		if (this->QMTable[this->iCurrState]->GetDecS() == -1)
		{
			iTemp = this->bMPS;
			this->bMPS = this->bLPS;
			this->bLPS = iTemp;
		}
	}

	this->Qe = this->QMTable[this->iCurrState]->GetQe();
}