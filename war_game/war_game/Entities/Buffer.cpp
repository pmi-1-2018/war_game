#include "Buffer.h"



void Buffer::BuffDamage(Unit& other_unit) 
{
	if (other_unit.GetDamage() <= 70)
	{
		other_unit.SetDamage(other_unit.GetDamage() + 10);
	}
}

void Buffer::BuffDefense(Unit& other_unit) 
{
	if (other_unit.GetDefense() <= 30)
	{
		other_unit.SetDefense(other_unit.GetDefense() + 5);
	}	
}