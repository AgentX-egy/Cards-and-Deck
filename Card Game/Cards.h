#pragma once
#include "SR.h"
class Cards
{
private:
	char CardID = NULL;
public:
	Cards(Ranks rank, Suites suite)
	{
		CardID |= (char)rank << 0;
		CardID |= (char)suite << 4;
	}
	Cards() : CardID(0){};
	friend std::ostream& operator << (std::ostream& out, const Cards& c);

public:
	Ranks getRank() const
	{
		return Ranks( CardID & 0x0F );
	}
	Suites getSuite() const
	{
		return Suites( (CardID & 0xF0) >> 4 );
	}
#ifdef _DEBUG
	char getCardID()
	{
		return CardID;
	}
#endif //only in debug mode
};

std::ostream& operator<<(std::ostream& os, const Cards& c)
{
	os << c.getRank() << " of " << c.getSuite();
	return os;
}
