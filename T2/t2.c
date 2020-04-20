#include <stdio.h>
#include <stdlib.h>

#include "t2.h"

// insertar_bits(0b10 1101, 3, 0b00, 2) es 0b1010 0101
// insertar_bits(0b11 0111, 0, 0b011, 3) es 0b1 1011 1011
// insertar_bits(0b1 0111, 2, 0b01110, 5) es 0b10 1011 1011


uint insertar_bits(uint x, int pos, uint y, int len) {
  int mask0 = ~((-1) << (pos)); //1s hasta pos..., después 0s
  uint x_tail= x & mask0;
  int mask1 = (-1) << (pos);//0s hasta pos..., después 1s
  uint x_head0 = x & mask1;
  uint x_head = x_head0 << len;
  uint x_final = x_tail | x_head;
  uint ins = y << pos;
  return x_final | ins;

}
