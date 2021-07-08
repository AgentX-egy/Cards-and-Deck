#pragma once
#define NoSUITES 4
enum class Suites
{
	DECK = 0b0000, SPADES = 0b1000, HEARTS = 0b0100, DIAMONDS = 0b0010, CLUBS = 0b0001
};
#define NoRANKS 13
enum class Ranks
{
	END = 0, ACE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6, SEVEN = 7, EIGHT = 8, NINE = 9, TEN = 10, JACK = 11, QUEEN = 12, KING = 13
};