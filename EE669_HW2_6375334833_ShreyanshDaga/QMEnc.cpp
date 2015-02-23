#include "HW_2.h"
#include "QMEnc.h"

QMEnc::QMEnc()
{

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