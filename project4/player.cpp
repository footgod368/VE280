#include <iostream>
#include "player.h"

using namespace std;

bool drawSoft(const Card &cardOfDealer, const Hand &handOfPlayer);
bool drawHard(const Card &cardOfDealer, const Hand &handOfPlayer);

class SimplePlayer : public Player
{
    int bet(unsigned int bankroll, unsigned int minimum) override
    {
        return minimum;
    }
    bool draw(Card dealer, const Hand &player) override
    {
        if (player.handValue().soft)
            return drawSoft(dealer, player);
        return drawHard(dealer, player);
    }
    void expose(Card c) override{};
    void shuffled() override{};
};

static SimplePlayer simplePlayer;

extern Player *get_Simple()
{
    return &simplePlayer;
}

bool drawSoft(const Card &cardOfDealer, const Hand &handOfPlayer)
{
    int curCount = handOfPlayer.handValue().count;
    if (curCount <= 17)
        return true;
    if (curCount == 18)
        return !(cardOfDealer.spot == TWO ||
                 cardOfDealer.spot == SEVEN ||
                 cardOfDealer.spot == EIGHT);
    return false;
}
bool drawHard(const Card &cardOfDealer, const Hand &handOfPlayer)
{
    int curCount = handOfPlayer.handValue().count;
    if (curCount <= 11)
        return true;
    if (curCount == 12)
        return !(cardOfDealer.spot >= FOUR && cardOfDealer.spot <= SIX);
    if (curCount >= 13 && curCount <= 16)
        return !(cardOfDealer.spot >= TWO && cardOfDealer.spot <= SIX);
    return false;
}

class CountingPlayer : public Player
{
private:
    int count;

public:
    CountingPlayer() : count(0) {}
    int bet(unsigned int bankroll, unsigned int minimum) override
    {
        if (count >= 2 && bankroll >= 2 * minimum)
            return 2 * minimum;
        else
            return minimum;
    }
    bool draw(Card dealer, const Hand &player) override
    {
        if (player.handValue().soft)
            return drawSoft(dealer, player);
        return drawHard(dealer, player);
    }
    void expose(Card c) override
    {
        if (c.spot <= SIX)
            count += 1;
        else if (c.spot >= TEN)
            count -= 1;
    }
    void shuffled() override
    {
        count = 0;
    }
};

static CountingPlayer countingPlayer;
extern Player *get_Counting()
{
    return &countingPlayer;
}
