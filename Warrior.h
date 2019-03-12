#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;


class Warrior {
	int hp;
	int damage = 100;
	int armor = 500;

public:
	Warrior() :hp(0) {};
	Warrior(int warriorHealth, int warriorDamage, int warriorArmor)
	{
		hp = warriorHealth;
		damage = warriorDamage;
		armor = warriorArmor;
	}
	int getHp() {
		return hp;
	}
	int getArmor()
	{
		return armor;
	}
	int getDamage()
	{
		return damage;
	}
	friend istream&operator>>(istream&is, Warrior &war) {
		is >> war.hp;
		return is;
	}



};
