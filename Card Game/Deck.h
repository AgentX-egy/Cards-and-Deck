#pragma once
#include <iostream>
#include "Cards.h"
class Deck
{
private:
	Cards c;
	Deck* nC;
private:
	Deck() : c(), nC(nullptr) {}
	Deck(Cards c) : c(c), nC(nullptr) {}

public:
	void append(Deck& deck)
	{
		this->nC = &deck;
	}
	void pop()
	{
		if (this->nC != nullptr)
		{
			*this = *this->nC;
		}
	}
public:
	static Deck createDeck()
	{
		Deck top;
		Deck* current = &top;
		
		Suites suite = Suites::SPADES;
		Ranks rank = Ranks::ACE;
		for (int scounter = 0; scounter < NoSUITES; suite++, scounter++)
		{
			for (int rcounter = 0; rcounter < NoRANKS; rank++, rcounter++)
			{
				current->c = Cards(rank, suite);
				Deck* tail = new Deck();
				current->append(*tail);
				current = tail;
			}
		}
		return top;
	}
	static void printDeck(Deck& deck)
	{
		std::cout << deck.c << std::endl;
		if (deck.nC != nullptr)
		{
			printDeck(*deck.nC);
		}
	}
	static Deck& cut(Deck& deck, int at)
	{
		Deck* newCut = deck.nC;
		for (int index = 2; index < at; index++)
		{
			newCut = newCut->nC;
		}
		if (newCut != nullptr)
		{
			Deck& lastOld = *newCut;
			lastOld.nC = nullptr;
		}
		return *newCut;
	}
};
