#pragma once
#include "Barrack.h"

class BarrackBuffer : public Barrack
{
public:
	BarrackBuffer()
	{
		numberOfUnits = 3;
	}
	Unit giveUnit()
	{
		Buffer unit;
		return unit;
	}
	string TellType()
	{
		return "barrack of buffers";
	}

};