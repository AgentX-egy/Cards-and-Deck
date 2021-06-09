#pragma once
#include <iostream>
#include "Cards.h"
namespace {
	class CardsQueue {
	public:
		Cards card;
		CardsQueue* nextCard;

	public:
		CardsQueue() : card(), nextCard(nullptr) {}
		CardsQueue(Cards card) : card(card), nextCard(nullptr) {}

	public:
		void append(CardsQueue* const card)
		{
			this->nextCard = card;
		}
		Cards& pop()
		{
			Cards& card = this->card;
			if (this->nextCard != nullptr)
			{
				*this = *this->nextCard; //flaw? pop doesn't delete the node
			}
			else
			{
				//delete this;
				//TO-DO: deleting the last card in the queue should make the prev->nextCard = nullptr
				//errors Deck::pickACard
			}
			return card;
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
				newCut = newCut->nextCard;
			}
			if (newCut != nullptr)
			{
				lastOld = this->deckBottom;
				this->deckBottom = newCut;

				firstNew = newCut->nextCard;
				newCut->nextCard = nullptr;
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
				newCut = newCut->nextCard;
			}
			lastNew = newCut;
			for (int i = from; i < to; i++)
			{
				lastNew = lastNew->nextCard;
			}
			if (lastNew != nullptr)
			{
				firstNew = newCut->nextCard;
				newCut->nextCard = lastNew->nextCard;
				lastNew->nextCard = nullptr;
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
			if (this->deckBottom->nextCard == nullptr)
			{
				this->deckBottom->nextCard = other.deckTop;
				this->deckBottom = other.deckBottom;
			}
			else
			{
				//error
			}
		}
		inline void appened(Deck* other)
		{
			appened(*other);
		}
		void insert(Deck& other, const int& at)
		{
			CardsQueue* current = this->deckTop;
			CardsQueue* post = current->nextCard;
			for (int i = 1; i < at; i++)
			{
				current = current->nextCard;
				post = current->nextCard;
			}
			if (other.deckBottom->nextCard == nullptr)
			{
				current->nextCard = other.deckTop;
				other.deckBottom->nextCard = post;
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
				current = current->nextCard;
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
		void riffle(const int& size = 52, const int& margin = 3)
		{
			const int cutAt = (rand() % (margin * 2)) + (size / 2 - margin);
			const Deck* const newCut = this->cut(cutAt);
			CardsQueue* otherA = newCut->deckTop;
			CardsQueue* otherB = this->deckTop;
			while (otherA != newCut->deckBottom && otherB != this->deckBottom)
			{
				CardsQueue* temp = otherA->nextCard;
				otherA->nextCard = otherB->nextCard;
				otherB->nextCard = otherA;

				otherB = otherA->nextCard;
				otherA = temp;
			}
			if (otherB == this->deckBottom)
			{
				otherB->nextCard = otherA;
				this->deckBottom = newCut->deckBottom;
			}
			else if (otherA == newCut->deckBottom)
			{
				CardsQueue* temp = otherB->nextCard;
				otherB->nextCard = otherA;
				otherA->nextCard = temp;
			}
			else
			{
				/* deckBottom will naturally be correct in a perfect ruffle */
			}
		}
		inline void perfectRiffle(const int& size = 52)
		{
			riffle(size, 1);
		}
		void print()
		{
			CardsQueue* printNext = this->deckTop;
			do
			{
				std::cout << printNext->card << std::endl;
				printNext = printNext->nextCard;
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
