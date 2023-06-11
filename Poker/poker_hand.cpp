#include "poker_hand.hpp"

#include <algorithm>	//fill, max_element


namespace {  /*  ary def  */
  FIG  typef[14] = {};
  FIG  shape[ 5] = {};
  SUIT types[ 5] = {};
}

namespace {  /*  declaration  */
  void resetAry();
  void setAry(const HAND& _hand);

  int8_t judgeSub();

  bool isFlash();
  bool isAceHighStraight();
  bool isStraight();
}


namespace {  /*  definition  */

void resetAry()
{
#if 1
  std::fill(typef, typef + 14, 0);
  std::fill(shape, shape +  5, 0);
  std::fill(typef, types +  5, 0);
#else
  for (auto i = 0; i < 14; ++i)
    typef[i] = 0;
  for (auto i = 0; i <  5; ++i) {
    shape[i] = 0;
    types[i] = 0;
  }
#endif
}

void setAry(const HAND& _hand)
{
  for (auto i = 0; i < _hand.size(); ++i) {
    types[_hand[i][0]] += 1;	//suit
    typef[_hand[i][1]] += 1;	//figure
  }
  for (auto i = 1; i < 14; ++i)
    shape[typef[i]] += 1;

  shape[0] = typef[0];
}

int8_t
judgeSub()
{
#if 1
  auto tmp  = shape[2]; tmp += shape[3];
       tmp += shape[4]; tmp -= shape[1];
  switch(tmp) {
#else
  switch(shape[2] + shape[3] + shape[4] - shape[1]) {
#endif
  case -2:
//  case -4:
    return 1;	//One Pair
  case -1:
//  case -3:
    return 3;	//Three of Kinds
  case  2:
    return 6;	//Full House
  case  0:
    return 7;	//Four of Kinds
  case  1:
    return	//Two Pair and Five of Kinds
      shape[0] ? 10 : 2;
  default:
    return	//No Pair and others
      isFlash() ?
        isAceHighStraight() ?
          9 :
          isStraight() ?
            8 :
            5 :
        isStraight() ?
          4 :
          shape[0] ?
            shape[0]-1 ?
              3 :
              1 :
            0 ;
  }
  return -1;   //err
}


bool
isFlash()
{
  return *std::max_element(types + 1, types + 5) + types[0] >= 5;
}

bool
isAceHighStraight()
{
  if (!typef[1] && !typef[0]) return false;
  auto tmp  = typef[ 0]; tmp += typef[ 1];
       tmp += typef[10]; tmp += typef[11];
       tmp += typef[12]; tmp += typef[13];
  return tmp >= 5;
}

bool
isHighStraight(const int8_t n)
{
  if (n < 5 || n > 13) return false;
  if (!typef[n] && !typef[0]) return false;
  auto tmp  = typef[ 0];
  for (auto i = 0; i < 5; ++i)
    tmp += typef[n-i];
  return
    tmp >= 5 ?
      typef[n-4] ?
        true  :
        false :
      false ;
}

bool
isStraight()
{
  if (isAceHighStraight()) return true;
  for (auto i = 1; i < 10; ++i) {
    auto tmp = typef[ 0];
    for (auto j = 0; j < 5; ++j)
      tmp += typef[i + j];
    if (tmp >= 5)
      return true;
  }
  return false;
}

}

int8_t
judgePokerHand
  (const HAND & _hand)
{
  resetAry();
  setAry(_hand);
  return judgeSub();
}




/*

NP  0  F   5
OP  1  FH  6
TP  2  FoK 7
ToK 3  SF  8
S   4  RF  9
*/



