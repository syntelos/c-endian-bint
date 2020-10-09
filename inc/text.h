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
#ifndef _syntelos_text_h
#define _syntelos_text_h

#include "syntelos.h"

/*
 * From user encoding input to machine encoding output
 */
typedef char* (*text_value_read)(char*);
/*
 * From machine encoding input to user encoding output
 */
typedef char* (*text_value_write)(char*);
/*
 * Given a user hex nibble, return a machine integer at bit string
 * shift offset zero.
 */
uint64_t text_uint4_hex_read(char u);

#define text_uint4_hex_read_error 0xFF
/*
 * Given a machine nibble at bit string shift offset zero, return a
 * user hex nibble.
 */
char text_uint4_hex_write(uint64_t m);

#define text_uint4_hex_write_error 0x0

/*
 * Require "0X" (or "0x") prefix on user format.  Require null
 * terminal, or full width (zero padded 64b) representation.
 * 
 * Returns eight bytes from the malloc plane with value encoded to
 * system byte order.
 */
char* text_uint64_hex_read(char* u);
/*
 * Produce "0x" prefix on user format.  Produce full width (64b zero
 * padded) representation.
 * 
 * Returns a null terminated string.
 */
char* text_uint64_hex_write(char* m);
/*
 * Read POSIX date format to a 64 bit integer number of seconds
 * (time_t) since the unix epoch.
 */
char* text_datetime_read(char*);
/*
 * Write POSIX date format to a 32 byte buffer in the malloc memory
 * plane.
 */
char* text_datetime_write(char*);
/*
 * Buffer length used for DATETIME user output strings (32 B).
 */
#define TEXT_DATETIME_BUFZ 32

#endif
