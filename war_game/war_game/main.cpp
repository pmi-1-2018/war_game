#include <iostream>
#include <string>
#include <ctime>
#include "Utils/Menu.h"
using namespace std;

int main() {
	srand(time(NULL));
	Menu menu;
	menu.PrintMenu();
	menu.KeyHandler();
	system("pause");
	return 0;
}