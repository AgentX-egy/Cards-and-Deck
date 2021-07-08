#pragma once
#include <iostream>
#include "Cards.h"
#include "Deck.h"

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

std::ostream& operator<<(std::ostream& os, const Cards& card)
{
	os << card.getRank() << " of " << card.getSuite();
	return os;
}

void printDeck(AX::Deck& deck)
{
	const CardsQueue* printNext = deck.getDeckTop();
	do
	{
		std::cout << printNext->card << std::endl;
		printNext = printNext->nextCard;
	} while (printNext != nullptr);
}