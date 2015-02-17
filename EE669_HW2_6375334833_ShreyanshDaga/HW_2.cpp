#include "HW_2.h"

int main(char args[])
{
	int iCh = 0;

	while (1)
	{
		iCh = PrintMenu();
		switch (iCh)
		{
			case 1:
			{
				Problem_1_A();
			}
			break;

			case 2:
			{
				Problem_1_B();
			}
			break;

			case 3:
			{
				Problem_2_A();
			}
			break;

			case 4:
			{
				Problem_2_B();
			}
			break;

			case 5:
			{
				Problem_3_A();
			}
			break;

			case 6:
			{
				Problem_3_B();
			}
			break;

			case 7:
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
	


	return iCh;
}
