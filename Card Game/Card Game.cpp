// Card Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Deck.h"

int main()
{
	{
		Deck::Deck d = Deck::deck52();
		std::cout << d.pickACard(51) <<std::endl; //choosing 52 will case error as it's the last cards, see ::pop();
	}
}
