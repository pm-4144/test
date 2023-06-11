
#include "poker.hpp"

#include "poker_hand.hpp"
#include "operator.hpp"

#include <iostream>
#include <iomanip>


namespace {

const char *rank_str[11] = {
 "No Pair",
 "One Pair",
 "Two Pair",
 "Three of Kinds",
 "Straight",
 "Flash",
 "Full House",
 "Four of Kinds",
 "Straight Flash",
 "Royal Flash",
 "Five of Kinds"
};

using HANDS = std::vector<HAND>;
using v8    = std::vector<int8_t>;

}


namespace {  /*  declaration  */
  void dealCards(CARDS & _stack,
                 HAND  & _hand );
  void dealCards(CARDS & _stack,
                 HANDS & _hands);
  void printHand(const HAND& _hand);
  void discardCards(CARDS & _stack,
                    HAND  & _hand );
  void printRank(const HAND  & _hand );
  void printRank(const HANDS & _hands);
  bool isOver();
  void clearHands (CARDS & _stack,
                   HAND  & _hand );
}

namespace {  /*  definition  */

void
dealCards
  (CARDS & _stack,
   HAND  & _hand )
{
  for (auto i = 0; i < 5; ++i)
    _hand.drawCard(_stack);
}

void
dealCards
  (CARDS& _stack,
   HANDS& _hands)
{
  for (auto i = 0; i < 5; ++i)
    for (auto& j : _hands)
      j.drawCard(_stack);
}

void printHand(const HAND& _hand) {
  for (int i = 0; i < _hand.size(); ++i)
    std::cout << '\t' << i;
  std::cout << "\tq\n";

  for (const auto& v : _hand) {
    std::cout << '\t';
    std::cout << getSuit(v);
    std::cout << getFig(v) ;
  }
  std::cout << "\tQuit\n";
}


void
discardCards
  (CARDS & _stack,
   HAND  & _hand )
{
  v8 tmp;
  std::string _ord;
  for (auto i = 0; ; ++i) {
    std::cin >> _ord;
    if (_ord == "q" || _ord == "Q") break;
    if ("0" <= _ord && _ord <  "5") {
      int8_t j = std::stoi(_ord);
      tmp += j;
    }
  }

  CARDS rt = {};
  for (const auto& w : tmp)
    rt += _hand[w];
  _hand() -= rt;

  for (const auto& i : rt) {
    _hand.drawCard(_stack);
    _stack += i;
  }
}

void
printRank
  (const HAND & _hand)
{
  auto i = judgePokerHand(_hand);  
  std::cout << rank_str[i] << std::endl;
}

void
printRank
  (const HANDS & _hands)
{
  auto s = _hands.size();
  v8 tmp(s);
  for (auto i = 0; i < s; ++i)
    tmp[i] = judgePokerHand(_hands[i]);
  for (auto i = 0; i < s; ++i)
    std::cout << std::setw(15) << "    : " << (!i ? "YOU" : "NPC" + std::to_string(i)); 
  std::cout << std::endl;
  for (const auto& i : tmp)
    std::cout << std::setw(15) << rank_str[i];
  std::cout << std::endl;
}


bool isOver() {
  while (true) {
    std::cout << "Do you continue? (Yes(Y) or No(N))" << std::endl;
    std::string str;
    std::cin >> str;
    if (str == "y" || str == "Y" || str == "Yes" || str == "yes") {
      return true;
    }
    if (str == "n" || str == "N" || str == "No" || str == "no") {
      return false;
    }
  }
  return true;
}

void clearHands
  (CARDS & _stack,
   HAND  & _hand )
{
  _stack += _hand();
  _hand().clear();
}

/*
void doPoker(int _numJk) {
  CARDS stack(_numJk);
  bool flag = true;
  while (flag) {
    dealCards(stack);
    printHand();
    discardCards(stack);
    printHand();
    printRank();
    flag = isOver();
    clearHands(stack);
    stack.shuffleCards();
  }
}

void doPokerinD4DJ() {
  CARDS stack;
  bool flag = true;
  while (flag) {
    hands[0].drawCard(stack);
    hands[0].drawCard(stack);
    dealCards(stack);
    printHand();
    setArray(hands[0]);
    cout << rank_str[calcRankinD4DJ()] << endl;
    flag = isOver();
    clearHands(stack);
    stack.shuffleCards();
  }  //Poker in D4DJ

}

void test(int _numJk) {
  CARDS stack(_numJk);
  long num_rank[11]={0,0,0,0,0,0,0,0,0,0,0};
  bool flag = true;
  for (long i=0; i<1024*1024; i++) {
    dealCards(stack);
    calcRank();
    num_rank[rank[0]] += 1;
    clearHands(stack);
    stack.shuffleCards();
  }
  for (int i=0; i<11; i++) {
    cout << num_rank[i] << " ";
  }
  cout << endl;
  return;
}
*/
}

void
test
  (int8_t _numJk)
{
  CARDS stack{};
    initDeck(stack, _numJk);

  int32_t tmp[11] = {};

  int32_t max = stack.size();
  for (auto i0 = 0; i0 < max; ++i0)
  for (auto i1 = i0+1; i1 < max; ++i1)
  for (auto i2 = i1+1; i2 < max; ++i2)
  for (auto i3 = i2+1; i3 < max; ++i3)
  for (auto i4 = i3+1; i4 < max; ++i4)
  {
    HAND hand = {};      hand() += stack[i0];
    hand() += stack[i1]; hand() += stack[i2];
    hand() += stack[i3]; hand() += stack[i4];
    tmp[judgePokerHand(hand)] += 1;
  }

  max = 0;
  for (auto i = 0; i < 11; ++i)
    max += tmp[i];

  std::cout << max << std::endl;

  for (auto i = 0; i < 11 ; ++i)
    std::cout << " " << tmp[i];
  std::cout << std::endl;

  for (auto i = 0; i < 11 ; ++i)
    std::cout << " " << std::fixed << std::setprecision(7) << (double)tmp[i]/max;
  std::cout << std::endl;
}

void
playTest
  (int8_t _numJk)
{
  CARDS stack{};
    initDeck(stack, _numJk);

  int32_t tmp[11] = {};
  int32_t max = 1024*1024/2;
  std::cout << max << std::endl;

  for(auto i = 0; i < max; ++i) {
    shuffleCards(stack);

    HAND hand{};
      dealCards(stack, hand);

    tmp[judgePokerHand(hand)] += 1;

    clearHands(stack, hand);
  }

  for (auto i = 0; i < 11 ; ++i)
    std::cout << " " << tmp[i];
  std::cout << std::endl;

  for (auto i = 0; i < 11 ; ++i)
    std::cout << " " << std::fixed << std::setprecision(7) << (double)tmp[i]/max;
  std::cout << std::endl;
}


void
playPoker
  (const int8_t _numJk)
{
  CARDS stack{};
    initDeck(stack, _numJk);

  bool flag = true;
  while (flag) {
    shuffleCards(stack);

    HAND hand{};
      dealCards(stack, hand);

    printHand(hand);
    discardCards(stack, hand);
    printHand(hand);

    printRank(hand);

    flag = isOver();
    clearHands(stack, hand);
  }
}

void playPoker
  (int8_t _num  ,
   int8_t _numJk)
{
  CARDS stack{};
    initDeck(stack, _numJk);
  HANDS hands(_num);

  bool flag = true;
  while (flag) {
    shuffleCards(stack);
    dealCards(stack, hands);
  
    printHand(hands[0]);
    discardCards(stack, hands[0]);
    printHand(hands[0]);
  
    printRank(hands);
  
    flag = isOver();
    for (auto& i : hands)
      clearHands(stack, i);
  }
}

/*
SF a,b;
a <  b :- a.max < b.max || (a = (1,...,5) < b (a != b) )
a == b :- a.min == b.min
Ex. D(2,3,4,5,6) < S(7,8,9,10,J)
    D(2,3,4,5,6) == S(2,3,4,5,6)

FoK a = x^4y, b = z^4w;
a < b :-  x < z. (x == z && y < w)
(a == b :- x == z && y == w)

FH a = x^3y^2, b = z^3w^2;
a < b :- x == z ? y < w : x < z
a = b :- x == z && y == w

F a,b;
a < b :- tie(a.max,...,a.min) < tie(b.max,...,b.min)
a == b :- ... == ...

S a,b;
a < b :- a.max < b.max
a == b :- a.max = b.max

ToK a = x^3yz,b = s^3tu; (y>z,t>u for FIG)
a < b :- x == s ? tie(y,z) < tie(t,u) : x < s
a = b tie(x,y,z) == tie(s,t,u)

TP
...

OP
...



*/




