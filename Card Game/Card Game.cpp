// Card Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Deck.h"
int main()
{
	Deck::Deck* deck = Deck::deck52();
	deck->flip();
	deck->print();
}
