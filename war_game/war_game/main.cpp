#include <iostream>
#include <string>
#include <ctime>
#include "Entities/Army.h"
#include "Utils/Menu.h"
using namespace std;

int main() 
{

	Army a;
	a.inputTheArmy();
	a.printArmy();
	Army b;
	b.inputTheArmy();
	b.printArmy();
	//a.armyAutoAttack(b);
	//a.battlePVE(b);
	a.battlePVP(b);
	//srand(time(NULL));
	//Menu menu;
	//menu.PrintMenu();
	//menu.KeyHandler();
	//system("pause");
	//return 0;
}