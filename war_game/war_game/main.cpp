#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "Utils/Menu.h"
#include "Windows.h"


using namespace std;

void set_color() 
{
	const char* val = "color 2";
	const int notUsed = system(val);
}

int main() {
	srand(time(NULL));
	Menu menu;
	menu.PrintMenu();
	menu.KeyHandler();
	/*for (int i=0;i<256;i++) 
	{
		cout << i << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
	}
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut,
		BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE);
	cout << "21 ## 3 # 34 5872" << endl;
	SetConsoleTextAttribute(hStdOut,
		BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_RED);
	cout << "E" << endl;
	SetConsoleTextAttribute(hStdOut,
		BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE | FOREGROUND_BLUE);
	cout << "D" << endl;
	SetConsoleTextAttribute(hStdOut,
		BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE | FOREGROUND_RED);
	cout << "#" << endl;*/
	system("pause");
	return 0;
}