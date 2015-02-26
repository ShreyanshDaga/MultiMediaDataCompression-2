#include "LMaxSQ.h"

LMaxSQ::LMaxSQ()
{

}

void LMaxSQ::TrainImgaes(string *strFiles, int iFileNum, int iNumBits)
{
	// Plot Histograms

	// Set Q Level
	this->SetQLevel(iNumBits);

}

void LMaxSQ::PlotHistograms(string *strFiles, int iFileNum)
{

}

void LMaxSQ::SetQLevel(int iNumBits)
{
	this->L = pow(iNumBits, 2);
}

void LMaxSQ::InitIntervals()
{
	// Allocate Size for TPoints and Centroids
	this->pfTPoints = new float[this->L+1];
	this->pfCentroids = new float[this->L];

	// Init TPoints
	this->pfTPoints[0] = 0;
	this->pfTPoints[this->L] = 255;

	// Compute Interval Size for Uniform Intv
	float fIntvSize = (float)(255.00)/this->L;

	// Compute Centroid Points for uniform Intv
	for (int i = 0; i < this->L; i++)
	{
		this->pfCentroids[i] = (i + 0.5) * fIntvSize;
	}
}

void LMaxSQ::CalculateIntervals()
{
	for (int i = 1; i < this->L; i++)
	{
		this->pfTPoints[i] = (this->pfCentroids[i] + this->pfCentroids[i - 1]) / 2;
	}
}

void LMaxSQ::CalculateNewLevels(unsigned short *puHist)
{
	for (int i = 0; i < this->L; i++)
	{

	}
}

void LMaxSQ::PrintTPoints()
{

}

void LMaxSQ::PrintCentroids()
{

}

float LMaxSQ::GetMSE(unsigned char *pcTrainingData)
{
	float fMSE = 0, fDiff, fQvalue;

	for (int i = 0; i < this->iFinalSize; i++)
	{
		unsigned char cByte = pcTrainingData[i];
		fQvalue = this->GetQValue(cByte);
		fDiff = pow((cByte - fQvalue),2);
		fMSE += fDiff;
	}

	fMSE /= this->iFinalSize;

	return fMSE;
}

float LMaxSQ::GetQValue(unsigned char cByte)
{
	if (cByte == 255) // If Max
	{
		return this->pfCentroids[this->L - 1];
	}

	for (int i = 0; i < this->L; i++)
	{
		if (cByte >= this->pfTPoints[i] && cByte < this->pfTPoints[i + 1]);
		return this->pfCentroids[i];
	}
}


float LMaxSQ::ComputeDistortionRate(float fPrevMSE, float fCurrMSE)
{
	return ((fPrevMSE - fCurrMSE) / (fCurrMSE));
}

void LMaxSQ::WriteTrainingStats()
{

}

void LMaxSQ::WriteFinalStats()
{

}