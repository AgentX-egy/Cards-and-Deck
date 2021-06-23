// Card Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Deck.h"

int main()
{
	Deck::Deck d = Deck::deck52();
	int size = 52;
	int arr[]
	{
		41,  5, 34, 40, 17, 26, 24, 18, 34, 40,
		35, 19,  1, 18,  5, 10,  7,  7, 33, 24,
		 7,  3,  2,  8, 12, 16,  1, 16, 14,  0,
		13, 12, 11,  5, 15,  5,  3,  4, 11,  1,
		11,  7,  2,  3,  1,  1,  3,  5,  3,  3,
		 1,  0
	};
	for (size_t i = 0; i < size; i++)
	{
		d.insert(d.pickACard(arr[i]), arr[i]);
	}
	d.print();
	std::cout << "\n------------------------------\n" << std::endl;
	for (size_t i = 0; i < size; i++)
	{
		std::cout << d.pickACard(rand()%size) << std::endl; 
		//imagine needing a riffle functions to get the same output
		//p.s.: riffle was easier to code than pickACard :(
		//p.s.s: they both took way to long, why am I doing this? ITS A LINKED LIST!?!
	}
}
