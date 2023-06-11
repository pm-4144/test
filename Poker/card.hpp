#pragma once

#include <compare>	//<=>, c++20

//	#include <algorithm>	//sort, shuffle
//	#include <vector>	//vector
//	#include <tuple>	//tie
//	#include <random>	//random_device, mt19937
////	#include <random>	//rand, srand
////	#include <ctime>	//time


using SUIT = int8_t;
using FIG = int8_t;



/* CLASS CARD */
/*************************************************************************************************/
class CARD{
  SUIT suit;	//suit
  FIG  fig;	//figures

public:
/* constructor */
/********************************************/
CARD() { suit = fig = 0; }
CARD(SUIT _suit, FIG _fig) { suit = _suit; fig = _fig; }

/*  Element access  */
      int8_t& operator[](size_t n)      &  { return n ? fig : suit ; }
const int8_t& operator[](size_t n) const&  { return n ? fig : suit ; }
//      int8_t  operator[](size_t n) const&& { return std::move( ); }

//const auto& operator()() const& { return 0; }

/* accessor */
CARD& Set(SUIT _suit, FIG _fig) { suit = _suit; fig = _fig; return *this; }
CARD& Joker() { return Set(0,0); }


/* operator */


};

/* non-member function */
//	CARD& setCard(int _suit, int _fig) { return CARD::CARD(_suit, _fig); }
const char *getSuit(const CARD& _card);
const char *getFig (const CARD& _card);

/* operator */
std::strong_ordering
//          auto
 operator <=> (const CARD& _this, const CARD& _that);
//constexpr bool operator ==  (const CARD& _this, const CARD& _that);

inline
constexpr bool
  operator ==
  (const CARD& _this,
   const CARD& _that)
{
  return
    _this[0] == _that[0] &&
    _this[1] == _that[1] ;
}



