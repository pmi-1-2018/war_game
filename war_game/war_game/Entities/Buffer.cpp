#include "Buffer.h"



void Buffer::BuffDamage(Unit& other_unit) 
{
	if (other_unit.getDamageBuff() <= 70)
	{
		other_unit.setDamageBuff(other_unit.getDamageBuff() + 10);
	}
}

void Buffer::BuffDefense(Unit& other_unit) 
{
	if (other_unit.getDefenseBuff() <= 30)
	{
		other_unit.setDefenseBuff(other_unit.getDefenseBuff() + 5);
	}	
}