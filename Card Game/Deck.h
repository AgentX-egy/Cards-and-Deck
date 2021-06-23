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
		CardsQueue(const Cards& card) : card(card), nextCard(nullptr) {}
		~CardsQueue() = default;
		CardsQueue(const CardsQueue& other) : card(other.card), nextCard(other.nextCard) {}
		CardsQueue(CardsQueue&& other) noexcept :
			card(std::move(other.card)), nextCard(std::exchange(other.nextCard, nullptr)) {}
	public:
		void operator delete(void* ptr)
		{
			if (ptr != nullptr)
			{
				delete& ((CardsQueue*)ptr)->card;
				((CardsQueue*)ptr)->nextCard = nullptr;
			}
			else {}
		}
		void operator delete[](void* ptr)
		{
			if (ptr != nullptr)
			{
				delete[]((CardsQueue*)ptr)->nextCard;
				delete ((CardsQueue*)ptr);
			}
			else {} //recursively delete the entire queue, takes N+1 space
		}
			CardsQueue& operator =(const CardsQueue& other)
		{
			this->card = other.card;
			this->nextCard = other.nextCard;
			return *this;
		}
		CardsQueue& operator =(CardsQueue&& other) noexcept
		{
			*this = other;
			delete& other;
			return *this;
		}
	public:
		void append(CardsQueue* const card)
		{
			this->nextCard = card;
		}
		Cards pop()
		{
			Cards card = this->card;
			if (this->nextCard != nullptr)
			{
				*this = std::move(*this->nextCard); //pop deletes the node
			}
			else
			{
				delete this; //deletes the last card in the queue 
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
	public:
		~Deck()
		{
			delete[] this->deckTop; // delete Cards/CardsQueue at end of scope as they are created on the heap
		}
	private:
		Deck(const Deck& other) = delete;
		Deck& operator =(const Deck& other) = delete;
	private:
		void* operator new(std::size_t size) = delete; //Deck is made up of two pointers, no need to create them on the heap
		void operator delete(void* ptr) = delete; //Deck is only ever created on the stack
		friend Deck deck52();
	public:
		const CardsQueue* const getDeckTop()
		{
			return deckTop;
		}
	public:
		Deck cut(int at)
		{
			CardsQueue* lastOld = this->deckBottom;
			CardsQueue* firstNew = this->deckTop;
			if (at > 0)
			{
				CardsQueue* newCut = firstNew;
				while (at --> 1 && newCut != lastOld)
				{
					newCut = newCut->nextCard;
				}
				if (newCut != lastOld)
				{
					firstNew = newCut->nextCard;
					this->deckBottom = newCut;

					newCut->nextCard = nullptr;
				}
				else
				{
					lastOld = nullptr;
					firstNew = nullptr;
				}
			}
			else
			{
				this->deckTop = nullptr;
				this->deckBottom = nullptr;
			}
			return Deck(firstNew, lastOld);
		}
		Deck cut(int from, int to)
		{
			CardsQueue* lastNew = nullptr;
			CardsQueue* firstNew = nullptr;
			if (from <= to)
			{
				CardsQueue dummy = CardsQueue();
				CardsQueue* connector = &dummy;
				CardsQueue* traverser = this->deckTop;
				if (from != 0)
				{
					to -= from;
					while (from --> 1 && traverser != this->deckBottom)
					{
						traverser = traverser->nextCard;
					}
					connector = traverser;
					traverser = traverser->nextCard; //The last from-- to make it 0
				}
				firstNew = traverser;
				while (to --> 0 && traverser != this->deckBottom)
				{
					traverser = traverser->nextCard;
				}
				if (firstNew == this->deckTop)
				{
					this->deckTop = traverser->nextCard;
				}
				if (traverser == this->deckBottom)
				{
					this->deckBottom = connector;
				}
				connector->nextCard = traverser->nextCard; //does nothing if connector == dummy
				lastNew = traverser;
				lastNew->nextCard = nullptr;
				//TO-DO: error if to != 0
			}
			else
			{
				//error
			}
			return Deck(firstNew, lastNew);
		}
		void appened(Deck& other)
		{
			this->deckBottom->nextCard = other.deckTop;
			this->deckBottom = other.deckBottom;
		}
		void insert(Deck& other, int at)
		{
			CardsQueue* current = this->deckTop;
			CardsQueue* post = current->nextCard;
			while (at --> 0 && post != this->deckBottom)
			{
				current = current->nextCard;
				post = current->nextCard;
			}
			current->nextCard = other.deckTop;
			other.deckBottom->nextCard = post;
		}
		void insert(CardsQueue* other, int at)
		{
			if (at > 0)
			{
				CardsQueue* prev = this->deckTop;
				CardsQueue* current = prev->nextCard;
				while (at --> 1 && current != this->deckBottom)
				{
					prev = prev->nextCard;
					current = prev->nextCard;
				}
				prev->nextCard = other;
				other->nextCard = current;
			}
			else
			{
				other->nextCard = this->deckTop;
				this->deckTop = other;
			}
		}
		inline void insert(const CardsQueue& other, const int& at)
		{
			insert(new CardsQueue(std::move(other)), at);
		}
		inline void insert(const Cards& cards, const int& at)
		{
			insert(new CardsQueue(cards), at);
		}
		Cards pickACard(int at)
		{
			Cards card;
			CardsQueue* prev = this->deckTop;
			CardsQueue* current = prev->nextCard;
			if (at > 0 && current != nullptr)
			{
				while (at --> 1 && current != this->deckBottom)
				{
					prev = current;
					current = current->nextCard;
				}
				const bool isLastCard = (current == this->deckBottom);
				card = current->pop();
				if (isLastCard)
				{
					this->deckBottom = prev;
					prev->nextCard = nullptr;
				}
				else if (current->nextCard == nullptr) //current was pre-last
				{
					this->deckBottom = current;
				}
				else {}
			}
			else
			{
				/*
				* Note on why not use prev->pop():
				* when deleting the last card, which is always indext/at 0,
				* pop deletes it perfectly fine, however Deck obj still holdes a pointer (topDeck)
				* to the deleted card. When the destructor is invoked, deleteing an already deleted node
				* doesn't play out well. Specifically, ((CardsQueue*)ptr)->nextCard = nullptr;
				*/
				card = prev->card;
				this->deckTop = current;
				delete prev;
			}
			return card;
		}
		void riffle(const int& size = 52, const int& margin = 3)
		{
			const int cutAt = (rand() % (margin * 2)) + (size / 2 - margin);
			Deck dummy = this->cut(cutAt);
			const Deck* const newCut = &dummy;
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

	Deck deck52()
	{
		CardsQueue dummy = CardsQueue();
		CardsQueue* deckTop = &dummy;
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
		deckTop = deckTop->nextCard;
		return Deck(deckTop, deckBottom);
	}
}
