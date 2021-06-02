// Card Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Deck.h"

using namespace std;
int main()
{
	Deck d = Deck::createDeck();
	d.cut(13);
	d.printDeck(d);
}
