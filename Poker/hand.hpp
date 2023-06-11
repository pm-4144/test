#pragma once

#include "cards.hpp"

#include <algorithm>


class HAND {
  CARDS hand;

public:

/*  Element access  */
      CARD& operator[](size_t n)      &  { return hand[n]; }
const CARD& operator[](size_t n) const&  { return hand[n]; }
      CARD  operator[](size_t n) const&& { return std::move(hand[n]); }

      auto& operator()()      & { return hand; }
const auto& operator()() const& { return hand; }

/* accessor */
void drawCard(CARDS& _stack) {
//  hand.reserve(hand.size() + 1);
  hand.push_back(_stack[0]);
  _stack.erase(_stack.begin());
}

void discard(int8_t i = 0) {
  if ( 0 <= i && i < hand.size())
    hand.erase(hand.begin() + i);
}

void discard(CARDS& _stack, int8_t i = 0) {
  if ( 0 <= i && i < hand.size()) {
    _stack.push_back(hand[i]);
    discard(i);
  }
}

constexpr auto begin()       noexcept { return hand.begin(); }
constexpr auto begin() const noexcept { return hand.begin(); }
constexpr auto end()         noexcept { return hand.end()  ; }
constexpr auto end()   const noexcept { return hand.end()  ; }

constexpr auto size() const noexcept { return hand.size(); }


void sort()
{
#if 0
  std::sort(begin(), end(),
    [] (const CARD& _this,
        const CARD& _that)
    {
      return
        _this[1] == _that[1] ?
          _that[0] < _this[0] :
          _this[1] < _that[1] ;
    }
  );
#else
  std::sort(begin(), end());
#endif
}



};


