#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "Utils/Menu.h"


int main() {
	srand(time(NULL));
	Menu menu;
	menu.PrintMenu();
	menu.KeyHandler();
	
	system("pause");
	return 0;
}