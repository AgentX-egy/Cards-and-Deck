#pragma once
#include "SR.h"
class Cards
{
private:
	char CardID=0;
public:
	Cards() = default;
	Cards(Ranks rank, Suites suite)
	{
		CardID |= (char)rank << 0;
		CardID |= (char)suite << 4;
	}

public:
	Ranks getRank() const
	{
		return Ranks( CardID & 0x0F );
	}
	Suites getSuite() const
	{
		return Suites( (CardID & 0xF0) >> 4 );
	}
};
