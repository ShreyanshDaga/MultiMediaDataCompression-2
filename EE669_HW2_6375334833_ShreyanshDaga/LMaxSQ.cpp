#include "LMaxSQ.h"
#include "FileIO.h"

LMaxSQ::LMaxSQ()
{
	this->fDistRate = 1.00f;
	this->fPSNR = 0.00f;
	this->fCurrMSE = 0.00f;
	this->fFinalMSE = 0.00f;	
	this->iFinalSize = 0;
}

void LMaxSQ::SetTrainingImages(string *strFiles, int iFileNum, int iNumBits)
{
	// Set Images
	this->strTrainFiles = new string[iFileNum];	
	FileIO **pFiles = new FileIO*[iFileNum];
	
	for (int i = 0; i < iFileNum; i++)
	{
		this->strTrainFiles[i] = strFiles[i];
		pFiles[i] = new FileIO(this->strTrainFiles[i].c_str(), false);
		this->iFinalSize += pFiles[i]->GetFileSize();
	}
	
	// Allocate Total Memory
	this->pcTrainingData = new unsigned char[this->iFinalSize];

	// Get all the file content
	for (int i = 0; i < iFileNum; i++)
	{
		for (int j = 0; j < pFiles[i]->GetFileSize(); j++)
		{
			this->pcTrainingData[i*iFileNum + j] = pFiles[i]->fileBuffer[j];
		}
	}

	// Set Q Level
	this->SetQLevel(iNumBits);
}

void LMaxSQ::TrainImgaes()
{
	// Plot Histograms
	unsigned short *puHist = this->CalcHist(this->pcTrainingData);
	// Write histogram here
	/// DEBUG
	for (int i = 0; i < 256; i++)
		cout << " " << puHist[i];
	///
	// Prepare Uniform Intervals
	this->InitIntervals();

	// Start Iterations
	int iItCount = 1;
	this->CalculateIntervals();
	this->CalculateNewLevels(puHist);
	// Print Tpoints
	// Print Centroid Point
	this->fCurrMSE = this->GetMSE(this->pcTrainingData);
	// MSE for ItCount = 1 cout, to file
	this->fPSNR = 10 * log10f(pow(255, 2) / this->fCurrMSE);
	// Cout PSNR, to file
	while (this->fDistRate > 0.001)
	{
		// Cout ItCount, to file
		/// DEBUG
		cout << " " << iItCount;
		iItCount++;
		///
		this->CalculateIntervals();
		this->CalculateNewLevels(puHist);
		// Print T Points
		// Print Centroid Points
		this->fFinalMSE = this->fCurrMSE;
		this->fCurrMSE = this->GetMSE(this->pcTrainingData);
		this->fDistRate = this->ComputeDistortionRate(this->fFinalMSE, this->fCurrMSE);
		// Cout to file
		this->fPSNR = 10 * log10f(pow(255, 2) / this->fCurrMSE);
		// Cout PSNR to file
		/// DEBUG
		cout << " " << this->fPSNR;
		///
	}

	cout << "Training Done!";
}

unsigned short* LMaxSQ::CalcHist(unsigned char *pcData)
{
	unsigned short *puHist = new unsigned short[256];
	
	for (int i = 0; i < 256; i++) 
	{
		puHist[i] = 1;
	}

	unsigned char cByte;
	for (int i = 0; i < this->iFinalSize; i++) 
	{
		cByte = (unsigned char)pcData[i];
		puHist[cByte]++;
	}	

	return puHist;
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
		/// DEBUG
		cout << " " << pfCentroids[i];
		/// DEBUG
	}
}

void LMaxSQ::CalculateIntervals()
{
	for (int i = 1; i < this->L; i++)
	{
		this->pfTPoints[i] = (this->pfCentroids[i] + this->pfCentroids[i - 1]) / 2;
	}
}

// Calc new values of centroid
void LMaxSQ::CalculateNewLevels(unsigned short *puHist)
{
	int iN = 0, iD = 0, iLow, iHigh;

	for (int i = 0; i < this->L; i++)
	{
		iLow = ceilf(this->pfTPoints[i + 1]);

		if (i == this->L)
			iHigh = ceilf(this->pfTPoints[i + 1]);
		else
			iHigh = floorf(this->pfTPoints[i + 1]);

		iN = 0;
		iD = 0;

		for (int j = iLow; j <= iHigh; j++)
		{
			iN += j*puHist[j];
			iD += puHist[j];
		}

		if (iD != 0)
			this->pfCentroids[i] = ((float)iN / (float)iD);
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
		if (cByte >= this->pfTPoints[i] && cByte < this->pfTPoints[i + 1])
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

void LMaxSQ::Quantize(string fileName)
{
	FileIO fileIP(fileName.c_str(), false);
	
	FileIO fileOP("ouput_Q2_moon.raw", true);

	for (int i = 0; i < fileIP.GetFileSize(); i++)
	{
		unsigned char cIPByte = fileIP.fileBuffer[i];
		unsigned char cOPByte = floor(this->GetQValue(cIPByte) + 0.5);
		fileOP.WriteByteToFile(cOPByte);
	}

	// Write Final Statss
}