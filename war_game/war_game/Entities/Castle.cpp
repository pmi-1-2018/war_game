#include "Castle.h"
#include "BarrackArcher.h"
#include"BarrackSwordsman.h"
#include"BarrackTank.h"
#include"BarrackWizard.h"
#include"BarrackBuffer.h"
#include"BarrackHealer.h"
Barrack* Castle::getBarrack() {
	return barrack;
}
int Castle::getHealth() {
	return health;
}
string Castle::getNameOfArmy() {
	return nameOfArmy;
}
void Castle::fight() {
	// todo: realization of fighting in castle
	cout << "FIGHT IN CASTLE" << endl;
}
void Castle::setBarrack(int n) {
	if (n == 1)
	{
		this->barrack = new BarrackArcher();
	}
	else if (n == 2)
	{
		this->barrack = new BarrackSwordsman();
	}
	else if (n == 3)
	{
		this->barrack = new BarrackTank();
	}
	else if (n == 4)
	{
		this->barrack = new BarrackWizard();
	}
	else if (n == 5)
	{
		this->barrack = new BarrackBuffer();
	}
	else if (n == 6)
	{
		this->barrack = new BarrackHealer();
	}
}
void Castle::setPointerToOwnerOfGoldMine()
{
	this->goldMine.setPointerToOwner(this->pointerToOwner);
}
void Castle::setGoldMine(){
	this->goldMine = GoldMine();
}
void Castle::setPointerToOwner(Army* player)
{
	this->pointerToOwner = player;
}