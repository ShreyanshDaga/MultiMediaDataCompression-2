
#ifndef HW_2_H_
#define HW_2_H_

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

int PrintMenu();
string GenerateOpFileName(string strIpFileName, string strAppendText);

int** ComputeDCT(int iaBlock[16][16]);
int** ComputeQBlock(int **piaQ50, int iN);
int** Quantize(int **piaBlock, int **piaQN);
float GetPSNR(unsigned char *pComp, unsigned char *pOriginal, int iFileSize);

void Problem_1_B();
void Problem_2_A();
void Problem_2_B();
void Problem_3_A();
void Problem_3_B();
void Problem_3_C();

#endif