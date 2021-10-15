#include "¿Œ»—_2.h"

void main()
{
	cout << "1)Tests :: 2)Our own input ";
	int choice;
	string functionname;
	cin >> choice;
	cout << endl;
	switch (choice)
	{
	case 1: tests();
		break;
	case 2: our_own_input();
		break;
	default: cout << "Enter something possible to work with!";
		break;
	}
	system("pause"); 
}
