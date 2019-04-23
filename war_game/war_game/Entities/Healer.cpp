#include "Healer.h"

void Healer::Heal(Unit& other_unit)
{
	
	if (other_unit.GetHealthPoints() < other_unit.GetMaxHP())
	{
		other_unit.SetHealthPoints(other_unit.GetHealthPoints() + 10);
		if (other_unit.GetHealthPoints() > other_unit.GetMaxHP())
		{
			other_unit.SetHealthPoints(other_unit.GetMaxHP());
		}
	}
}