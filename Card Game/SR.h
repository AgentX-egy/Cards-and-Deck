#pragma once
#define NoSUITES 4
enum class Suites
{
	DECK = 0b0000, SPADES = 0b1000, HEARTS = 0b0100, DIAMONDS = 0b0010, CLUBS = 0b0001
};
std::ostream& operator<<(std::ostream& os, const Suites& suite)
{
	const char* s = "";
	switch (suite)
	{
	case Suites::SPADES:   s = "SPADES"; break;
	case Suites::HEARTS:   s = "HEARTS"; break;
	case Suites::DIAMONDS: s = "DIAMONDS"; break;
	case Suites::CLUBS:    s = "CLUBS"; break;
	case Suites::DECK:     s = "DECK"; break;
	}
	os << s;
	return os;
}
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

#define NoRANKS 13
enum class Ranks
{
	END = 0, ACE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6, SEVEN = 7, EIGHT = 8, NINE = 9, TEN = 10, JACK = 11, QUEEN = 12, KING = 13
};
std::ostream& operator<<(std::ostream& os, const Ranks& rank)
{
	const char* r = "";
	switch (rank)
	{
	case Ranks::END:   r = "END"; break;
	case Ranks::ACE:   r = "ACE"; break;
	case Ranks::TWO:   r = "TWO"; break;
	case Ranks::THREE: r = "THREE"; break;
	case Ranks::FOUR:  r = "FOUR"; break;
	case Ranks::FIVE:  r = "FIVE"; break;
	case Ranks::SIX:   r = "SIX"; break;
	case Ranks::SEVEN: r = "SEVEN"; break;
	case Ranks::EIGHT: r = "EIGHT"; break;
	case Ranks::NINE:  r = "NINE"; break;
	case Ranks::TEN:   r = "TEN"; break;
	case Ranks::JACK:  r = "JACK"; break;
	case Ranks::QUEEN: r = "QUEEN"; break;
	case Ranks::KING:  r = "KING"; break;
	}
	os << r;
	return os;
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
