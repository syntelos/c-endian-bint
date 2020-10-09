/*
 * Syntelos BINT
 * Copyright (C) 2020, John Pritchard, Syntelos
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * (LGPL and GPL) as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LGPL
 * and GPL for more details.
 *
 * You should have received a copy of the LGPL and GPL along with this
 * program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "bint.h"

bint_kind bint_kind_host(){
#if BINT_KIND == BINT_KIND_LE
  return bint_kind_le;
#elif BINT_KIND == BINT_KIND_BE
  return bint_kind_be;
#else
  return bint_kind_un;
#endif
}

/*
 * BE16 WORD { [1][0] }
 * 
 *  swap(1,0)
 */
uint16_t bint_swap_be16(uint16_t he){
#if BINT_KIND == BINT_KIND_LE
  bint16_t n;
  {
    n.value = he;
  }
  {
    uint8_t s;

    bint_swap_macro(n,s,1,0);
  }
  return n.value;
#else
  return he;
#endif
}
/*
 * BE32 WORD { [3][2][1][0] }
 * 
 *  swap(3,0)
 *  swap(2,1)
 */
uint32_t bint_swap_be32(uint32_t he){
#if BINT_KIND == BINT_KIND_LE
  bint32_t n;
  {
    n.value = he;
  }
  {
    uint8_t s;

    bint_swap_macro(n,s,3,0);
    bint_swap_macro(n,s,2,1);
  }
  return n.value;
#else
  return he;
#endif
}
/*
 * BE64 WORD { [7][6][5][4][3][2][1][0] }
 * 
 *  swap(7,0)
 *  swap(6,1)
 *  swap(5,2)
 *  swap(4,3)
 */
uint64_t bint_swap_be64(uint64_t he){
#if BINT_KIND == BINT_KIND_LE
  bint64_t n;
  {
    n.value = he;
  }
  {
    uint8_t s;

    bint_swap_macro(n,s,7,0);
    bint_swap_macro(n,s,6,1);
    bint_swap_macro(n,s,5,2);
    bint_swap_macro(n,s,4,3);
  }
  return n.value;
#else
    return he;
#endif
}
