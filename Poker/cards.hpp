#pragma once

#include "card.hpp"
#include <vector>


using CARDS = std::vector<CARD>;

constexpr int8_t suit_max =  4;
constexpr int8_t fig_max  = 13;
constexpr int8_t num_deck = suit_max*fig_max;


void initDeck(CARDS& _stack,
              int8_t _numJk);
void shuffleCards(CARDS& _stack);

