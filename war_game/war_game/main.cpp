#include <iostream>
#include <string>
#include <ctime>
#include "Windows.h"
#include "Entities/Army.h"
#include "Utils/Menu.h"
using namespace std;

int main() 
{
	unsigned int time_ui = static_cast<unsigned int>(time(NULL));
	srand(time_ui);
	Menu menu;
	menu.PrintMenu();
	menu.KeyHandler();
	
	//##color choosing
	/*const HANDLE HSTDOUT = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i=0; i < 255;i++)
	{
		SetConsoleTextAttribute(HSTDOUT, i);
		cout << i << ")   asdijqw[oijdqjoiwdijqw" << endl;
	}*/
	system("pause");
	return 0;
}