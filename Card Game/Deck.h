#pragma once
#include <utility>
#include "Cards.h"
namespace {
	class CardsQueue {
	public://members
		Cards card;
		CardsQueue* nextCard;
	public://constructors
		CardsQueue() : card(), nextCard(nullptr) {}
		CardsQueue(const Cards& card) : card(card), nextCard(nullptr) {}
	public://destructor
		~CardsQueue() = default;
	public://copiers
		CardsQueue(const CardsQueue& other) : card(other.card), nextCard(other.nextCard) {}
		CardsQueue& operator =(const CardsQueue& other)
		{
			this->card = other.card;
			this->nextCard = other.nextCard;
			return *this;
		}
	public://movers
		CardsQueue(CardsQueue&& other) noexcept :
			card(std::move(other.card)), nextCard(std::exchange(other.nextCard, nullptr)) {}
		CardsQueue& operator =(CardsQueue&& other) noexcept
		{
			*this = other;
			delete& other;
			return *this;
		}
	public://heap allocation
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
	public://members
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
namespace AX {
#define CardsQueue ::CardsQueue
	class Deck
	{
	private: //attributes
		CardsQueue* deckTop;
		CardsQueue* deckBottom;
	public://constructors
		Deck() = delete;
		Deck(CardsQueue*, CardsQueue*);
	public://destructor
		~Deck();
	private://copiers
		Deck(const Deck& other) = default;
		Deck& operator =(const Deck& other) = default;
	private://heap allocation
		void* operator new(std::size_t size) = delete; //Deck is made up of two pointers, no need to create them on the heap
		void operator delete(void* ptr) = delete; //Deck is only ever created on the stack
	public://gets-sets
		const CardsQueue* const getDeckTop()
		{
			return deckTop;
		}
	public://members
		Deck cut(int);
		Deck cut(int, int);
		void append(Deck&);
		void insert(Deck&, int);
		void insert(CardsQueue*, int);
		inline void insert(const CardsQueue&, const int&);
		inline void insert(const Cards&, const int&);
		Cards pickACard(int);
		void riffle(const int&, const int&);
		inline void perfectRiffle(const int&);
		void shuffle(const int&);
		void flip();
	public://static memebers
		static Deck deck52();
	};
}
