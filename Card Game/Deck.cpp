#include "Deck.h"
#include "incrementor++.h"
namespace AX
{
	Deck::Deck(CardsQueue* deckTop, CardsQueue* deckBottom) : deckTop(deckTop), deckBottom(deckBottom) {};
	Deck::~Deck()
	{
		delete[] this->deckTop; // delete Cards/CardsQueue at end of scope as they are created on the heap
	}
	Deck Deck::cut(int at)
	{
		CardsQueue* lastOld = this->deckBottom;
		CardsQueue* firstNew = this->deckTop;
		if (at > 0)
		{
			CardsQueue* newCut = firstNew;
			while (at-- > 1 && newCut != lastOld)
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
	Deck Deck::cut(int from, int to)
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
				while (from-- > 1 && traverser != this->deckBottom)
				{
					traverser = traverser->nextCard;
				}
				connector = traverser;
				traverser = traverser->nextCard; //The last from-- to make it 0
			}
			firstNew = traverser;
			while (to-- > 0 && traverser != this->deckBottom)
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
		/*
		* Cut is prone to errors as it returns a Deck obj which deletes its CardsQueue automatically.
		* An error may occure if the cards in the deck is refrenced elsewhere in another deck.
		* deck obj will delete the cards when out of scope, when the other deck try to delete the cards again, it leads to an error.
		* to avoid an error, make use you use append on one another or handel one of the decks so they don't refrence the same Cards obj.
		* e.g. deck.deckTop = nullptr; should suffice.
		*/
	}
	void Deck::append(Deck& other)
	{
		this->deckBottom->nextCard = std::exchange(other.deckTop, nullptr);
		this->deckBottom = std::exchange(other.deckBottom, nullptr);
	}
	void Deck::insert(Deck& other, int at)
	{
		CardsQueue* current = this->deckTop;
		CardsQueue* post = current->nextCard;
		while (at-- > 0 && post != this->deckBottom)
		{
			current = current->nextCard;
			post = current->nextCard;
		}
		current->nextCard = std::exchange(other.deckTop, nullptr);
		other.deckBottom->nextCard = post;
	}
	void Deck::insert(CardsQueue* other, int at)
	{
		if (at > 0)
		{
			CardsQueue* prev = this->deckTop;
			CardsQueue* current = prev->nextCard;
			while (at-- > 1 && current != this->deckBottom)
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
	inline void Deck::insert(const CardsQueue& other, const int& at)
	{
		insert(new CardsQueue(std::move(other)), at);
	}
	inline void Deck::insert(const Cards& cards, const int& at)
	{
		insert(new CardsQueue(cards), at);
	}
	Cards Deck::pickACard(int at)
	{
		Cards card;
		CardsQueue* prev = this->deckTop;
		CardsQueue* current = prev->nextCard;
		if (at > 0 && current != nullptr)
		{
			while (at-- > 1 && current != this->deckBottom)
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
	void Deck::riffle(const int& size = 52, const int& margin = 3)
	{
		const int cutAt = (rand() % (margin * 2)) + (size / 2 - margin);
		Deck dummy = this->cut(cutAt);
		const Deck* const newCut = &dummy; //readability, doesn't do anything
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
		dummy.deckTop = nullptr; //fix after the Big5 update, see Deck::Cut()
	}
	inline void Deck::perfectRiffle(const int& size = 52)
	{
		riffle(size, 1);
	}
	void Deck::shuffle(const int& size = 52)
	{
		const int cutAt1 = (rand() % (size - 2)) / 2 + 1;
		const int cutAt2 = (rand() % (size - 2)) / 2 + 1;
		{
			Deck d1 = this->cut(0, cutAt1);
			Deck d2 = this->cut(cutAt2);
			d2.append(d1);
			this->append(d2);
		}
		this->riffle(size);
	}
	void Deck::flip() {
		CardsQueue* prev = nullptr;
		CardsQueue* current = this->deckTop;
		while (current != nullptr) {
			CardsQueue* nextTemp = current->nextCard;
			current->nextCard = prev;
			prev = current;
			current = nextTemp;
		}
		this->deckBottom = this->deckTop;
		this->deckTop = prev;
	}
	Deck Deck::deck52()
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
