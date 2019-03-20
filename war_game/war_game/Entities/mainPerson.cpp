#include <iostream>
#include "Unit.h"
#include "Archer.h"
#include "Tank.h"
#include "Swordsman.h"
#include "Wizard.h"

using namespace std;

int main()
{
	Unit** unit = new Unit*[4];
	unit[0] = new Archer();
	unit[1] = new Tank();
	unit[2] = new Swordsman();
	unit[3] = new Wizard();

	for (int i = 0; i < 4; i++) {
		cout << "attack: " << unit[i]->GetDamage() << endl;
	}

	unit[2]->attack((*unit[1]));
	unit[1]->attack((*unit[2]));
	unit[3]->BuffDamage((*unit[2]));
	cout << unit[2]->DamageTaken() << endl;;
	cout << unit[1]->GetHealthPoints()<<endl;
	cout << unit[2]->GetDamage() << endl;

	system("pause");
	return 0;
}