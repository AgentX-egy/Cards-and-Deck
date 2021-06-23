// Card Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Deck.h"

int main()
{
	Deck::Deck d = Deck::deck52();
	srand(time(NULL));
	d.shuffle();
	d.print();
	{
		d.cut(4, 26);
	}
	std::cout << "\n----------------------\n" << std::endl;
	d.print();
	{
		//d = d.cut(10); decks lifetime cannot (and should not) be extended
		d.cut(10,999);
	}
	std::cout << "\n----------------------\n" << std::endl;
	d.print();
}
