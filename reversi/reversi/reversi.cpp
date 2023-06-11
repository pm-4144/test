//
//  reversi.cpp
//  reversi
//
//  Created by Pino Marianne on 2023/06/06.
//


#include "reversi.hpp"

#include <unordered_set>
#include <unordered_map>

namespace {
constexpr int black =  1;
//constexpr int null  =  0;
constexpr int white = -1;
}


namespace {
struct coord {
    int x, y;
    coord() = default;
    coord(int n)
    {
        x = y = n; x /= 8; y %= 8;
    }
    coord(std::initializer_list<int> il)
    : x(*il.begin()), y(*(il.begin()+1)) {}
    int operator()() const& { return 8*x+y; }
    bool unvalid() { return x<0 || 7<x || y<0 || 7<y; }
};

coord& operator +=(coord& lhs, const coord& rhs)
{
    lhs.x += rhs.x; lhs.y += rhs.y; return lhs;
}
const coord operator +(const coord& lhs, const coord& rhs)
{
    auto rt = lhs; return rt += rhs;
}
coord& operator -=(coord& lhs, const coord& rhs)
{
    lhs.x -= rhs.x; lhs.y -= rhs.y; return lhs;
}
const coord operator -(const coord& lhs, const coord& rhs)
{
    auto rt = lhs; return rt -= rhs;
}
}


namespace {
#if 1
std::unordered_set<int> search_range = {};
std::unordered_set<int> direction = {
    8, -8, 1, -1,
    9, -9, 7, -7
};
std::unordered_map<int,coord> dir_map = {
    {8,{1,0}}, {-8,{-1,0}}, {1,{0,1}}, {-1,{0,-1}},
    {9,{1,1}}, {-9,{-1,-1}}, {7,{1,-1}}, {-7,{-1,1}}
};
#endif
#if 0
std::unordered_set<coord> search_range = {};
std::unordered_set<coord> direction = {
    {1,0}, {-1,0}, {0,1}, {0,-1},
    {1,1}, {-1,-1}, {1,-1}, {-1,1}
};
#endif
}


#if 1
// cell
cell::cell(int state)
: state(state) {}
bool& cell::operator()(bool n) &
{
    return n ? black : white;
}
const bool& cell::operator()(bool n) const&
{
    return n ? black : white;
}

void cell::turnOver()
{
    state *= -1;
}
#endif

#if 1
// field
int& field::operator[](size_t n) &
{
    return x[n].state;
}
const int& field::operator[](size_t n) const&
{
    return x[n].state;
}
cell& field::operator()(size_t n) &
{
    return x[n];
}
const cell& field::operator()(size_t n) const&
{
    return x[n];
}

void field::operator++()
{
    for (const auto& i : search_range) {
        x[i].black = x[i].white = false;
        for (const auto& j : direction) {
            coord k = i; k += dir_map[j];
            if (k.unvalid()) continue;  // wheather is there a cell
            
            auto stat = x[k()].state;
            if(!stat) continue;  // wheather is there some piece
            
            for (auto h = k;; h += dir_map[j]) {
                if (h.unvalid()) {
                    stat = 0; break;
                }
                if (x[h()].state != stat) {
                    stat = x[h()].state;
                    break;
                }
            }
            if(!stat) continue;
            x[i](stat>0) = true;
        }
    }
}

field& field::init()
{
    search_range.clear();
    for (auto i = 0; i < 64; ++i)
        x[i] = cell();
    x[8*3+3] = x[8*4+4] = black;  //true , black,  1
    x[8*3+4] = x[8*4+3] = white;  //false, white, -1
    coord tmp{};
    tmp = {2,2}; search_range.emplace(tmp());
    tmp = {2,3}; search_range.emplace(tmp());
    tmp = {2,4}; search_range.emplace(tmp());
    tmp = {2,5}; search_range.emplace(tmp());
    tmp = {3,5}; search_range.emplace(tmp());
    tmp = {4,5}; search_range.emplace(tmp());
    tmp = {5,5}; search_range.emplace(tmp());
    tmp = {5,4}; search_range.emplace(tmp());
    tmp = {5,3}; search_range.emplace(tmp());
    tmp = {5,2}; search_range.emplace(tmp());
    tmp = {4,2}; search_range.emplace(tmp());
    tmp = {3,2}; search_range.emplace(tmp());
    
    ++(*this);
    //x[8*4+2].black = x[8*5+3].black = true;
    //x[8*2+4].black = x[8*3+5].black = true;
    //x[8*2+3].white = x[8*3+2].white = true;
    //x[8*4+5].white = x[8*5+4].white = true;
    return *this;
}
field& field::putPieceAt(bool color, int i, int j)
{
    coord pos = {i,j};
    auto n = pos();
    
    if (x[n].state) return *this;
    if (!x[n](color)) return *this;
    x[n].state = color ? black : white;
    x[n].black = x[n].white = false;
    search_range.erase(n);
    
    std::unordered_set<int>
        dir1 = {},  // direction of some neighbor piece put in an adjoint cell
        dir2 = {};  // direction of some adjoint cell having no piece
    for (const auto& k : direction) {
        auto m = pos; m += dir_map[k];
        if (m.unvalid()) continue;
        
        if (x[m()].state) {
            dir1.emplace(k);
            continue;
        } else {
            dir2.emplace(k);
            continue;
        }
#if 0
        switch (k()) {
            case  8:
            case -8:
                tmp.erase(k);
                tmp.erase(k+1);
                tmp.erase(k-1);
                tmp.erase( 1);
                tmp.erase(-1);
                break;
            case  1:
            case -1:
                tmp.erase(k);
                tmp.erase(k+8);
                tmp.erase(k-8);
                tmp.erase( 8);
                tmp.erase(-8);
                break;
            case  9:
            case -7:
                tmp.erase(k-1);
                tmp.erase(1);
                break;
            case  7:
            case -9:
                tmp.erase(k+1);
                tmp.erase(-1);
                break;
        }
        if (!tmp.size()) break;
#endif
    }
    
    // update : search_range
    for (const auto& i : dir2) {
        search_range.emplace(n+i);
    }
    
    // reverse some piece
    for (const auto& i : dir1) {
        auto k = pos; k += dir_map[i];
        auto stat = x[k()].state;
        if(x[n].state == stat) continue;
        
        for (auto h = k;; h += dir_map[i]) {
            if (h.unvalid()) {
                stat = 0; break;
            }
            if (x[h()].state != stat) {
                stat = x[h()].state;
                break;
            }
        }
        if(!stat) continue;
        for (auto h = k; x[h()].state != stat; h += dir_map[i]) {
            x[h()].state = stat;
        }
    }
    
    return *this;
}

#endif
