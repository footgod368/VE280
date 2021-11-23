#include <iostream>
#include <cassert>
#include "../hand.h"

using namespace std;

int main()
{
       Hand newHand;
       assert(newHand.handValue().count == 0 &&
              newHand.handValue().soft == false);
       newHand.addCard({JACK, HEARTS});
       assert(newHand.handValue().count == 10);
       newHand.addCard({ACE, HEARTS});
       assert(newHand.handValue().count == 21 &&
              newHand.handValue().soft == true);
       newHand.addCard({ACE, HEARTS});
       assert(newHand.handValue().count == 12 &&
              newHand.handValue().soft == false);
       newHand.discardAll();
       assert(newHand.handValue().count == 0 &&
              newHand.handValue().soft == false);
       newHand.addCard({TWO, HEARTS});
       newHand.addCard({THREE, HEARTS});
       newHand.addCard({KING, HEARTS});
       newHand.addCard({ACE, HEARTS});
       assert(newHand.handValue().count == 16 &&
              newHand.handValue().soft == false);
       return 0;
}