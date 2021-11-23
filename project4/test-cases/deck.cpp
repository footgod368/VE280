#include <iostream>
#include "deck.h"
#include "card.h"

using namespace std;

void resetDeck(Card deck[]);
void shuffle_helper(const Card leftDeck[], const int leftLen, const Card rightDeck[], const int rightLen, Card newDeck[]);

Deck::Deck() : next(0)
{
    resetDeck(deck);
}

Card Deck::deal()
{
    if (next > 51)
    {
        DeckEmpty deckEmpty;
        throw deckEmpty;
    }
    return deck[next++];
}

void Deck::reset()
{
    next = 0;
    resetDeck(deck);
}

int Deck::cardsLeft()
{
    return (DeckSize - next);
}

void Deck::shuffle(int n)
{
    Card newDeck[DeckSize];
    Card leftDeck[DeckSize];
    Card rightDeck[DeckSize];
    int leftLen = n;
    int rightLen = DeckSize - n;
    for (int i = 0; i <= n - 1; i++)
        leftDeck[i] = deck[i];
    for (int i = n; i <= DeckSize - 1; i++)
        rightDeck[i - n] = deck[i];

    shuffle_helper(leftDeck, leftLen, rightDeck, rightLen, newDeck);

    for (int i = 0; i <= DeckSize - 1; i++)
        deck[i] = newDeck[i];
    next = 0;
}

void resetDeck(Card deck[])
{
    for (int i = 0; i <= 51; i++)
    {
        Card newCard = {(Spot)(i % 13), (Suit)(i / 13)};
        deck[i] = newCard;
    }
}

void shuffle_helper(const Card leftDeck[], const int leftLen, const Card rightDeck[], const int rightLen, Card newDeck[])
{
    if (leftLen > 0 && rightLen > 0)
    {
        newDeck[0] = rightDeck[0];
        newDeck[1] = leftDeck[0];
        shuffle_helper(leftDeck + 1, leftLen - 1, rightDeck + 1, rightLen - 1, newDeck + 2);
    }
    else if (leftLen <= 0 && rightLen > 0)
    {
        for (int i = 0; i <= rightLen - 1; i++)
            newDeck[i] = rightDeck[i];
    }
    else if (leftLen > 0 && rightLen <= 0)
    {
        for (int i = 0; i <= leftLen - 1; i++)
            newDeck[i] = leftDeck[i];
    }
}
