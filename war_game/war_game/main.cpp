#include <iostream>
#include <string>
#include <ctime>
#include "Entities/Army.h"
#include "Utils/Menu.h"
using namespace std;

int main() 
{

	
	srand(time(NULL));
	Menu menu;
	menu.PrintMenu();
	menu.KeyHandler();
	system("pause");
	return 0;
}