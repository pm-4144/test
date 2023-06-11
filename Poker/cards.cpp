#include "cards.hpp"

#include <algorithm>
#include <random>
//#include <ctime>


void
initDeck
  (CARDS& _stack    ,
   int8_t _numJk = 0)
{
  _stack.resize(num_deck + _numJk);
  for (auto i = 0; i < fig_max; ++i) {
    _stack[            i].Set(1, i + 1);
    _stack[fig_max*1 + i].Set(2, i + 1);
    _stack[fig_max*2 + i].Set(3, i + 1);
    _stack[fig_max*3 + i].Set(4, i + 1);
  }
  for (auto i = 0; i < _numJk; ++i)
    _stack[num_deck + i].Joker();
}

void
shuffleCards
  (CARDS& _stack)
{
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  std::shuffle(_stack.begin(), _stack.end(), engine);
/*
  srand(time(NULL));
  for (auto i=_stack.size()-1; i>0; --i) {
    auto j = rand()%(i + 1);
    if (i == j) continue;
    auto tmp  = _stack[j];
    _stack[j] = _stack[i];
    _stack[i] = tmp;
  }
*/
}


