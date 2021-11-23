#include <iostream>
#include <cstdlib>
#include "player.h"
#include "deck.h"
#include "rand.h"
using namespace std;

class Driver
{
private:
    unsigned int bankroll;
    unsigned int minimum;
    int handsNum;
    int handsCount;
    int wager;
    Player *player;
    Deck deck;
    Hand handOfPlayer;
    Hand handOfDealer;
    Card cardOfDealer;
    Card holeCard;

public:
    Driver(int argc, char *argv[]);
    void shuffle();
    bool shouldContinue();
    void announceHand();
    bool shouldShuffle();
    void setWager();
    void firstDeal();
    bool isNatural();
    void winNaturally();
    void playerPlay();
    bool isPlayerBust();
    void playerBust();
    void announcePlayerTotal();
    void exposeHoleCard();
    void dealerPlay();
    bool shouldDealerDraw();
    bool isDealerBust();
    void dealerBust();
    void announceDealerTotal();
    void announceHandResult();
    void announceGameResult();
    void dicardAllCards();
};

int main(int argc, char *argv[])
{
    Driver driver(argc, argv);

    driver.shuffle();
    while (driver.shouldContinue())
    {
        driver.dicardAllCards();

        driver.announceHand();
        if (driver.shouldShuffle())
            driver.shuffle();
        driver.setWager();
        driver.firstDeal();
        if (driver.isNatural())
        {
            driver.winNaturally();
            continue;
        }
        driver.playerPlay();
        driver.announcePlayerTotal();
        if (driver.isPlayerBust())
        {
            driver.playerBust();
            continue;
        }
        driver.exposeHoleCard();
        driver.dealerPlay();
        driver.announceDealerTotal();

        if (driver.isDealerBust())
        {
            driver.dealerBust();
            continue;
        }
        driver.announceHandResult();
    }
    driver.announceGameResult();
    return 0;
}

Player *initPlayer(char mode[])
{
    string mode_(mode);
    if (mode_ == "counting")
        return get_Counting();
    return get_Simple();
}

Driver::Driver(int argc, char *argv[])
    : bankroll(atoi(argv[1])),
      minimum(5),
      handsNum(atoi(argv[2])),
      handsCount(0),
      wager(0),
      player(initPlayer(argv[3])) {}

void Driver::shuffle()
{
    cout << "Shuffling the deck\n";

    for (int i = 1; i <= 7; i++)
    {
        int cut = get_cut();
        cout << "cut at " << cut << endl;
        deck.shuffle(cut);
    }
    player->shuffled();
}

bool Driver::shouldContinue()
{
    return bankroll >= minimum && handsNum > handsCount;
}

void Driver::announceHand()
{
    handsCount++;
    cout << "Hand " << handsCount << " bankroll " << bankroll << endl;
}

bool Driver::shouldShuffle()
{
    return deck.cardsLeft() < 20;
}

void Driver::setWager()
{
    wager = player->bet(bankroll, minimum);
    cout << "Player bets " << wager << endl;
}

void Driver::firstDeal()
{
    Card firstCard = deck.deal();
    player->expose(firstCard);
    handOfPlayer.addCard(firstCard);
    cout << "Player dealt " << SpotNames[firstCard.spot] << " of " << SuitNames[firstCard.suit] << endl;

    cardOfDealer = deck.deal();
    player->expose(cardOfDealer);
    handOfDealer.addCard(cardOfDealer);
    cout << "Dealer dealt " << SpotNames[cardOfDealer.spot] << " of " << SuitNames[cardOfDealer.suit] << endl;

    Card thirdCard = deck.deal();
    player->expose(thirdCard);
    handOfPlayer.addCard(thirdCard);
    cout << "Player dealt " << SpotNames[thirdCard.spot] << " of " << SuitNames[thirdCard.suit] << endl;

    holeCard = deck.deal();
    handOfDealer.addCard(holeCard);
}

bool Driver::isNatural()
{
    return handOfPlayer.handValue().count == 21;
}

void Driver::winNaturally()
{
    bankroll += (3 * wager) / 2;
    cout << "Player dealt natural 21\n";
}

void Driver::playerPlay()
{
    while (player->draw(cardOfDealer, handOfPlayer) && !isPlayerBust())
    {
        Card newCard = deck.deal();
        handOfPlayer.addCard(newCard);
        player->expose(newCard);
        cout << "Player dealt " << SpotNames[newCard.spot] << " of " << SuitNames[newCard.suit] << endl;
    }
}

bool Driver::isPlayerBust()
{
    return handOfPlayer.handValue().count > 21;
}

void Driver::playerBust()
{
    cout << "Player busts\n";
    bankroll -= wager;
}

void Driver::announcePlayerTotal()
{
    int player_count = handOfPlayer.handValue().count;
    cout << "Player's total is " << player_count << endl;
}

void Driver::exposeHoleCard()
{
    cout << "Dealer's hole card is " << SpotNames[holeCard.spot] << " of " << SuitNames[holeCard.suit] << endl;
    player->expose(holeCard);
}

void Driver::dealerPlay()
{
    while (shouldDealerDraw() && !isDealerBust())
    {
        Card newCard = deck.deal();
        handOfDealer.addCard(newCard);
        player->expose(newCard);
        cout << "Dealer dealt " << SpotNames[newCard.spot] << " of " << SuitNames[newCard.suit] << endl;
    }
}

bool Driver::shouldDealerDraw()
{
    return handOfDealer.handValue().count < 17;
}

bool Driver::isDealerBust()
{
    return handOfDealer.handValue().count > 21;
}

void Driver::dealerBust()
{
    cout << "Dealer busts\n";
    bankroll += wager;
}

void Driver::announceDealerTotal()
{
    int dealer_count = handOfDealer.handValue().count;
    cout << "Dealer's total is " << dealer_count << endl;
}

void Driver::announceHandResult()
{
    int player_count = handOfPlayer.handValue().count;
    int dealer_count = handOfDealer.handValue().count;
    if (dealer_count > player_count)
    {
        cout << "Dealer wins\n";
        bankroll -= wager;
    }
    else if (dealer_count < player_count)
    {
        cout << "Player wins\n";
        bankroll += wager;
    }
    else
        cout << "Push\n";
}

void Driver::announceGameResult()
{
    cout << "Player has " << bankroll << " after "
         << handsCount << " hands\n";
}

void Driver::dicardAllCards()
{
    handOfDealer.discardAll();
    handOfPlayer.discardAll();
}