#include <iostream>
#include <algorithm>
#include <random>
#include <iomanip>
#include "conio.h"


using std::cout;
using std::endl;
using std::cin;


int main() {

int field[16] = {
  0,  1,  2,  3,
  4,  5,  6,  7,
  8,  9, 10, 11,
 12, 13, 14, 15
};


std::random_device seed_gen;
std::mt19937_64 engine(seed_gen());
std::shuffle(field, field+16, engine);

auto pos = 0;
for (auto i = 0; i < 16; ++i)
  if (!field[i]) { pos = i; break; }

auto print = [&](){
  for (auto i = 0; i < 16; ++i) {
    if(!(i%4)) cout << (!i ? "\n" : "|\n") << "+--+--+--+--+\n";
    cout << "|";
    if (i != pos) { cout << std::setw(2) << field[i]; }
    else { cout << "  "; }
  }
  cout << "|\n+--+--+--+--+\n";
};


while (true) {
  print();

  auto chr = getch();
  if (chr != 27) continue;
  chr = getch();
  if (chr != 91) continue;
  chr = getch();
  switch (chr) {
  case 65:  // up
    if (pos > 11) break;
    field[pos] = field[pos +4];
    field[pos += 4] = 0; break;
  case 66:  // down
    if (pos < 4) break;
    field[pos] = field[pos - 4];
    field[pos -= 4] = 0; break;
  case 67:  // right
    if (!(pos%4)) break;
    field[pos] = field[pos - 1];
    field[--pos] = 0; break;
  case 68:  // left
    if (pos%4 == 3) break;
    field[pos] = field[pos + 1];
    field[++pos] = 0; break;
  }


  auto flag = false;
  for (auto i = 0; i < 16; ++i)
    if (i != field[i]) { flag = true; break; }
  if (flag) continue;
  break;
}

print();

return 0;
}



