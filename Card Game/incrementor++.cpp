#include "incrementor++.h"

Suites operator++(Suites& s, int)
{
	switch (s)
	{
	case Suites::SPADES:   return s = Suites::HEARTS;
	case Suites::HEARTS:   return s = Suites::DIAMONDS;
	case Suites::DIAMONDS: return s = Suites::CLUBS;
	case Suites::CLUBS:    return s = Suites::SPADES;
	}
}
Ranks operator++(Ranks& r, int)
{
	switch (r)
	{
	case Ranks::ACE:   return r = Ranks::TWO;
	case Ranks::TWO:   return r = Ranks::THREE;
	case Ranks::THREE: return r = Ranks::FOUR;
	case Ranks::FOUR:  return r = Ranks::FIVE;
	case Ranks::FIVE:  return r = Ranks::SIX;
	case Ranks::SIX:   return r = Ranks::SEVEN;
	case Ranks::SEVEN: return r = Ranks::EIGHT;
	case Ranks::EIGHT: return r = Ranks::NINE;
	case Ranks::NINE:  return r = Ranks::TEN;
	case Ranks::TEN:   return r = Ranks::JACK;
	case Ranks::JACK:  return r = Ranks::QUEEN;
	case Ranks::QUEEN: return r = Ranks::KING;
	case Ranks::KING:  return r = Ranks::ACE;
	}
}