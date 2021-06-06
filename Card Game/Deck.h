#pragma once
#include <iostream>
#include "Cards.h"
namespace {
	class CardsQueue {
	public:
		Cards c;
		CardsQueue* nC;

	public:
		CardsQueue() : c(), nC(nullptr) {}
		CardsQueue(Cards c) : c(c), nC(nullptr) {}

	public:
		void append(CardsQueue* const card)
		{
			this->nC = card;
		}
		Cards& pop()
		{
			Cards& c = this->c;
			if (this->nC != nullptr)
			{
				*this = *this->nC; //flaw? pop doesn't delete the node
			}
			else
			{
				//delete this;
				//TO-DO: deleting the last card in the queue should make the prev->nC = nullptr
				//errors Deck::pickACard
			}
			return c;
		}

	};
}
namespace Deck {
	class Deck
	{
	private:
		CardsQueue* deckTop;
		CardsQueue* deckBottom;
	private:
		Deck() = delete;
		Deck(CardsQueue* deckTop, CardsQueue* deckBottom) : deckTop(deckTop), deckBottom(deckBottom) {}
		Deck(const Deck& other) : deckTop(other.deckTop), deckBottom(other.deckBottom) {}
		friend Deck* deck52();
	public:
		Deck* cut(int at)
		{
			CardsQueue* lastOld = nullptr;
			CardsQueue* firstNew = nullptr;
			CardsQueue* newCut = this->deckTop;
			for (int index = 1; index < at; index++)
			{
				newCut = newCut->nC;
			}
			if (newCut != nullptr)
			{
				lastOld = this->deckBottom;
				this->deckBottom = newCut;

				firstNew = newCut->nC;
				newCut->nC = nullptr;
			}
			else {}
			return new Deck(firstNew, lastOld);
		}
		Deck* cut(int from, int to)
		{
			CardsQueue* lastNew = nullptr;
			CardsQueue* firstNew = nullptr;
			CardsQueue* newCut = this->deckTop;
			for (int i = 1; i < from; i++)
			{
				newCut = newCut->nC;
			}
			lastNew = newCut;
			for (int i = from; i < to; i++)
			{
				lastNew = lastNew->nC;
			}
			if (lastNew != nullptr)
			{
				firstNew = newCut->nC;
				newCut->nC = lastNew->nC;
				lastNew->nC = nullptr;
				if (this->deckBottom == lastNew)
				{
					this->deckBottom = lastNew;
				}
				else {}
			}
			else {}
			return new Deck(firstNew, lastNew);
		}
		void appened(Deck& other)
		{
			this->deckBottom->nC = other.deckTop;
			this->deckBottom = other.deckBottom;
			delete& other;
		}
		inline void appened(Deck* other)
		{
			appened(*other);
		}
		void insert(Deck& other, const int& at)
		{
			CardsQueue* current = this->deckTop;
			CardsQueue* post = current->nC;
			for (int i = 1; i < at; i++)
			{
				current = current->nC;
				post = current->nC;
			}
			if (other.deckBottom->nC == nullptr)
			{
				current->nC = other.deckTop;
				other.deckBottom->nC = post;
			}
			else
			{
				//error
			}
		}
		inline void insert(Deck* other, const int& at)
		{
			insert(*other, at);
		}
		Cards& pickACard(int&& at)
		{
			CardsQueue* current = this->deckTop;
			for (int i = 1; i < at; i++)
			{
				current = current->nC;
			}
			return current->pop();
		}
		Cards& pickACard(int& size)
		{
			return pickACard((rand() % size--) + 1);
		}
		Cards& pickACard()
		{
			return pickACard((rand() % 52) + 1); //will error 1.9226% of the time. See Cards::Pop()
		}
		void ruffle(const int& size = 52, const int& margin = 3)
		{
			const int cutAt = (rand() % (margin * 2)) + (size / 2 - margin);
			const Deck* const newCut = this->cut(cutAt);
			CardsQueue* otherA = newCut->deckTop;
			CardsQueue* otherB = this->deckTop;
			while (otherA->nC != nullptr && otherB->nC != nullptr)
			{
				CardsQueue* temp = otherA->nC;
				otherA->nC = otherB->nC;
				otherB->nC = otherA;

				otherB = otherA->nC;
				otherA = temp;
			}
			if (otherB->nC == nullptr)
			{
				otherB->nC = otherA;
				this->deckBottom = newCut->deckBottom;
			}
			else if (otherA->nC == nullptr)
			{
				CardsQueue* temp = otherB->nC;
				otherB->nC = otherA;
				otherA->nC = temp;
			}
			else
			{
				/* deckBottom will naturally be correct in a perfect ruffle */
			}
		}
		inline void perfectRuffle(const int& size = 52)
		{
			ruffle(size, 1);
		}
		void print()
		{
			CardsQueue* printNext = this->deckTop;
			do
			{
				std::cout << printNext->c << std::endl;
				printNext = printNext->nC;
			} while (printNext != nullptr);
		}
	};

	Deck* deck52()
	{
		CardsQueue* deckTop = new CardsQueue();
		CardsQueue* deckBottom = deckTop;
		Suites suite = Suites::SPADES;
		Ranks rank = Ranks::ACE;
		for (int scounter = 0; scounter < NoSUITES; suite++, scounter++)
		{
			for (int rcounter = 0; rcounter < NoRANKS; rank++, rcounter++)
			{
				CardsQueue* current = new CardsQueue(Cards(rank, suite));
				deckBottom->append(current);
				deckBottom = current;
			}
		}
		deckTop->pop();
		return new Deck(deckTop, deckBottom);
	}
}
