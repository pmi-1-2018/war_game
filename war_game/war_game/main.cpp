#include <iostream>
#include <string>
#include <ctime>
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
	system("pause");
	return 0;
}