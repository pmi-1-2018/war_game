#include <iostream>
#include <vector>
#include <string>
#include "Utils/Menu.h"
using namespace std;

int main() {
	Menu menu;
	menu.PrintMenu();
	menu.KeyHandler();

	system("pause");
	return 0;
}