#include "card.hpp"
//#include <compare>	//<=>, c++20

namespace {
//      const char *suit_str[5] = {"", "D", "H", "S", "C"};
//      const char *suit_str[5] = {"", "♡", "♢", "♤", "♧"};
        const char *suit_str[5] = {"", "♥︎", "♦︎", "♠︎", "♣︎"};
//      const char *suit_str[5] = {"", "♥️", "♦️", "♠️", "♣️"};

        const char *fig_str[14] = {"Jk", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
//      const char *fig_str[14] = {"🃏", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};



/*
1 コントラクトブリッジのビッドにおいてはクラブ < ダイヤ < ハート < スペードの順
2 ファイブハンドレッドやプレフェランスではスペード < クラブ < ダイヤ < ハートの順
3 スカートではダイヤ < ハート < スペード < クラブ（鈴 < 心臓 < 木の葉 < ドングリ）の順
4 中国の多くのゲーム（鋤大Dなど）ではダイヤ < クラブ < ハート < スペードの順
 {"" , "♥︎" , "♦︎" , "♠︎" , "♣︎"} max = 0, ... , 4 = min
*/

//	constexpr int8_t flag = 1;

//	constexpr int8_t suit_ary[5] = {0, 1, 2, 3, 4};
	constexpr int8_t suit_ary[5] = {0, 3, 1, 2, 4};
//	constexpr int8_t suit_ary[5] = {0, 1, 2, 4, 3};
//	constexpr int8_t suit_ary[5] = {0, 4, 3, 1, 2};
//	constexpr int8_t suit_ary[5] = {0, 3, 1, 4, 2};
//	constexpr int8_t suit_ary[5][5]{suit_ary0, suit_ary1, suit_ary2, suit_ary3, suit_ary4};

}
/*
static constexpr auto
suitOrder(const size_t n)
{
  switch (flag) {
  case 1:
    return 0;
  }
}
*/



/* non-member function */
//      CARD& setCard(int _suit, int _fig) { return CARD::CARD(_suit, _fig); }

const char *
getSuit
  (const CARD& _card)
{
  return suit_str[suit_ary[_card[0]]];
}

const char *
getFig
  (const CARD& _card)
{
  return fig_str[_card[1]];
}

/* operator */
/********************************************/
std::strong_ordering
//auto
  operator <=>
  (const CARD& _this,
   const CARD& _that)
{
  return
    _this[1] == _that[1] ?
      _that[0] <=> _this[0] :
      _this[1] <=> _that[1] ;
}

#if 0
constexpr bool
  operator ==
  (const CARD& _this,
   const CARD& _that)
{
  return
    _this[0] == _that[0] &&
    _this[1] == _that[1] ;
}
#endif





