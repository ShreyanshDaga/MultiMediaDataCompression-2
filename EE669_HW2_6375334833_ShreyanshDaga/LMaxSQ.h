#ifndef LMAXSQ_H_
#define LMAXSQ_H_

#include "HW_2.h"

class LMaxSQ
{
	private:
		int L;
		float *pfCentroids;
		float *pfTPoints;
		float fDistRate;
		float fCurrMSE;
		float fFinalMSE;
		float fPSNR;
		unsigned char *pcTrainingData;
		int iNumIter;
		string *strTrainFiles;
		int iFinalSize;

	public:
		LMaxSQ();

		void TrainImgaes(string *strFiles, int iFileNum, int iNumBits);
		void PlotHistograms(string *strFiles, int iFileNum);
		void SetQLevel(int iNumBits);
		void InitIntervals();
		void CalculateIntervals();
		void CalculateNewLevels(unsigned short *puHist);
		void PrintTPoints();
		void PrintCentroids();
		float GetMSE(unsigned char *pcTrainingData);
		float GetQValue(unsigned char cByte);
		float ComputeDistortionRate(float fPrevMSE, float fCurrMSE);
		void WriteTrainingStats();
		void WriteFinalStats();
};

#endif // !LMAXSQ_H_
