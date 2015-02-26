#include "HW_2.h"
#include "FileIO.h"
#include "QMEnc.h"

void TestFileIO();
void TestQMTableLoad()
{
	QMEnc enc;

	enc.LoadQMTable("QM_state_transition_table.txt");

}

void WriteTestFile()
{
	FileIO file("test_file.dat", true);

	// First Byte
	file.WriteBitToFile(1);
	file.WriteBitToFile(0);
	file.WriteBitToFile(0);
	file.WriteBitToFile(0);
	file.WriteBitToFile(1);
	file.WriteBitToFile(1);
	file.WriteBitToFile(0);
	file.WriteBitToFile(0);
	// Second Byte
	file.WriteBitToFile(1);
	file.WriteBitToFile(0);
	file.WriteBitToFile(0);
	file.WriteBitToFile(0);
	file.WriteBitToFile(1);
	file.WriteBitToFile(1);
	file.WriteBitToFile(0);
	file.WriteBitToFile(1);
	// Third Byte
	file.WriteBitToFile(1);
	file.WriteBitToFile(0);
	file.WriteBitToFile(0);
	file.WriteBitToFile(1);
	file.WriteBitToFile(0);
	file.WriteBitToFile(1);
	file.WriteBitToFile(1);
	file.WriteBitToFile(0);
	// Fourth Byte
	/*file.WriteBitToFile(1);
	file.WriteBitToFile(1);
	file.WriteBitToFile(1);
	file.WriteBitToFile(1);
	file.WriteBitToFile(1);
	file.WriteBitToFile(0);
	file.WriteBitToFile(0);
	file.WriteBitToFile(1);
*/
	file.CloseFile();

	FileIO file2("test_file.dat", false);
	file2.PreProcessFile();
}

int main(char args[])
{
	//TestFileIO();
	//TestQMTableLoad();
	//WriteTestFile();
	int iCh = 0;

	while (1)
	{
		iCh = PrintMenu();
		switch (iCh)
		{			
			case 1:
			{
				Problem_1_B();
			}
			break;

			case 2:
			{
				Problem_2_A();
			}
			break;

			case 3:
			{
				Problem_2_B();
			}
			break;

			case 4:
			{
				Problem_3_A();
			}
			break;

			case 5:
			{
				Problem_3_B();
			}
			break;

			case 6:
			{
				Problem_3_C();
			}
			break;

			case 0:
				return 0;
		}
	}	
}

int PrintMenu()
{
	int iCh = 0;
	
	system("CLS");
	cout << "\t\tShreyansh Daga, USCID 6375334833\n\n";
	cout << "******* Home work 2 ********\n";
	cout << "* Problem 1 : QM Coder\n";	
	cout << "1 Q1(b) Encoding using QM Coder\n\n";
	cout << "* Problem 2 : Scalar and Vector Quantization\n";
	cout << "2 Q2(a) Scalar Quantization\n";
	cout << "3 Q2(b) Vector Quantization\n\n";
	cout << "* Problem 3 : JPEG Compression\n";
	cout << "4 Q3(a) DCT and Quantization\n";
	cout << "5 Q3(b) JPEG Compression Quality Factor\n";
	cout << "6 Q3(c) Post-Processing for JPEG\n\n";
	cout << "0 Exit\n\n";
	cout << "\nEnter your choice: ";
	cin >> iCh;


	return iCh;
}

void TestFileIO()
{
	// Writing to File
	FileIO fileWrite("Test_1.dat", true);

	// Write a byte
	fileWrite.WriteBitToFile(1);
	fileWrite.WriteBitToFile(0);
	fileWrite.WriteBitToFile(1);
	fileWrite.WriteBitToFile(0);
	fileWrite.WriteBitToFile(1);
	fileWrite.WriteBitToFile(0);
	fileWrite.WriteBitToFile(1);
	fileWrite.WriteBitToFile(0);

	fileWrite.WriteBitToFile(0);
	fileWrite.WriteBitToFile(0);
	fileWrite.WriteBitToFile(1);
	fileWrite.WriteBitToFile(1);
	fileWrite.WriteBitToFile(0);
	fileWrite.WriteBitToFile(0);
	fileWrite.WriteBitToFile(0);
	fileWrite.WriteBitToFile(0);

	fileWrite.WriteLastByte();

	// Reading from File
	FileIO fileRead("text.dat", false);
	
	int iInt;
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n";
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n";
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n";
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();
	//cout << "\n" << fileRead.ReadBitFromFile();

	cin >> iInt;

	fileRead.CloseFile();
}
