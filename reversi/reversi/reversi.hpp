//
//  reversi.hpp
//  reversi
//
//  Created by Pino Marianne on 2023/06/06.
//

#ifndef reversi_hpp
#define reversi_hpp


#include <iostream>

struct cell {
    int state;
    bool black = {};  //wheather one is abel to put a black piece
    bool white = {};  //wheather one is abel to put a white piece
    
    cell() = default;
    cell(int state);
    
    bool& operator()(bool n) &;
    const bool& operator()(bool n) const&;
    
    void turnOver();
};

struct field {
    cell x[64] = {};
    
    field() = default;
    
    int& operator[](size_t n) &;
    const int& operator[](size_t n) const&;
    cell& operator()(size_t n) &;
    const cell& operator()(size_t n) const&;
    
    void operator++();
    
    field& init();
    field& putPieceAt(bool color, int i, int j);
};


#endif /* reversi_hpp */
