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
#ifndef _syntelos_bint_h
#define _syntelos_bint_h

#include "syntelos.h"

/*
 * https://sourceforge.net/p/predef/wiki/Endianness/
 */
typedef enum bint_kind {
  /*
   * The endianness is unknown.  The byte order swap functions will
   * have no effect.  (Note that the "middle endian" cases are
   * believed to be archaic and have not been handled).
   */
  bint_kind_un = 0,
  /*
   * The endianness is known to be "little".  
   */
  bint_kind_le = 1,
  /*
   * The endianness is known to be "big".  
   */
  bint_kind_be = 2

} bint_kind;

typedef union bint16_t {
  uint16_t value;
  uint8_t data[sizeof(uint16_t)];
} bint16_t;

typedef union bint32_t {
  uint32_t value;
  uint8_t data[sizeof(uint32_t)];
} bint32_t;

typedef union bint64_t {
  uint64_t value;
  uint8_t data[sizeof(uint64_t)];
} bint64_t;

/*
 * (bint_swap_macro) User example
 * 
 * BE64 WORD { [7][6][5][4][3][2][1][0] }
 * 
 *   bint64_t n;
 *   {
 *     n.value = fun_in_arg;
 *   }
 *   {
 *     uint8_t s;
 *
 *     bint_swap_macro(n,s,7,0);
 *     bint_swap_macro(n,s,6,1);
 *     bint_swap_macro(n,s,5,2);
 *     bint_swap_macro(n,s,4,3);
 *   }
 *   return n.value;
 */
#define bint_swap_macro(n,s,a,b) \
  s = n.data[a];                 \
  n.data[a] = n.data[b];         \
  n.data[b] = s;

/*
 * Determine host system endianness dynamically.
 */
bint_kind bint_kind_host();
/*
 * The same code performs be-to-he and he-to-be because the
 * distinction is no more than an encoding difference, and the
 * encoding difference is the symmetrical swap.
 */
uint16_t bint_swap_be16(uint16_t);

uint32_t bint_swap_be32(uint32_t);

uint64_t bint_swap_be64(uint64_t);
/*
 * bint_he_to_be16
 */
#if BINT_KIND == BINT_KIND_LE
#define bint_he_to_be16(b) bint_swap_be16(b)
#define bint_be_to_he16(b) bint_swap_be16(b)
#else
#define bint_he_to_be16(b) (b)
#define bint_be_to_he16(b) (b)
#endif
/*
 * bint_he_to_be32
 */
#if BINT_KIND == BINT_KIND_LE
#define bint_he_to_be32(b) bint_swap_be32(b)
#define bint_be_to_he32(b) bint_swap_be32(b)
#else
#define bint_he_to_be32(b) (b)
#define bint_be_to_he32(b) (b)
#endif
/*
 * bint_he_to_be64
 */
#if BINT_KIND == BINT_KIND_LE
#define bint_he_to_be64(b) bint_swap_be64(b)
#define bint_be_to_he64(b) bint_swap_be64(b)
#else
#define bint_he_to_be64(b) (b)
#define bint_be_to_he64(b) (b)
#endif

#endif
