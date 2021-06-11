// Card Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Deck.h"
Deck::Deck* makeDeck(const int& size) {
	CardsQueue dummy = CardsQueue();
	CardsQueue* deckTop = &dummy;
	CardsQueue* deckBottom = deckTop;
	for (int rcounter = 1; rcounter < size + 1; rcounter++)
	{
		CardsQueue* current = new CardsQueue(Cards((Ranks)rcounter, Suites::DECK));
		deckBottom->append(current);
		deckBottom = current;
	}
	deckTop = deckTop->nextCard;
	return new Deck::Deck(deckTop, deckBottom);
}

#define RUN_TEST0 1
#define RUN_TEST1 0
int main()
{
#if RUN_TEST0
	{
		//CutAt(int) TestCases
		int testCases[] = { -5, 0, 1, 4, 5, 800 };
		printf("running TEST0\n...........");
		for (int i = 0; i < 6; i++)
		{
			printf("\nTESTCASE-%d\n", i);
			Deck::Deck* deck = makeDeck(5);
			Deck::Deck* x = deck->cut(testCases[i]);
			(deck->deckTop != nullptr) ? deck->print() : (void)printf("deck set to nullptr\n");
			printf("----------\n");
			(x->deckTop != nullptr) ? x->print() : (void)printf("deck set to nullptr\n");
		}
	}
#endif
#if RUN_TEST1
	{
		//CutAt(int,int) TestCases
		int testCases[5][2] = { {2,3}, {0,2}, {1,4}, {0,4}, {3,3} };
		printf("running TEST1");
		for (int i = 0; i < 5; i++)
		{
			printf("\nTESTCASE-%d\n", i);
			Deck::Deck* deck = makeDeck(5);
			Deck::Deck* x = deck->cut(testCases[i][0], testCases[i][1]);
			(deck->deckTop != nullptr) ? deck->print() : (void)printf("deck set to nullptr\n");
			printf("----------\n");
			(x->deckTop != nullptr) ? x->print() : (void)printf("deck set to nullptr\n");
		}
	}
#endif
}
