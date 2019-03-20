#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "Utils/Menu.h"
#include "Windows.h"
using namespace std;


int main() {
	srand(time(NULL));
	Menu menu;
	menu.PrintMenu();
	menu.KeyHandler();
	/*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 7);*/
	system("pause");
	return 0;
}