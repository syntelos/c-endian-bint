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
#include "text.h"
#include "bint.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>

static const char posix_date_format[] = "%a %b %e %H:%M:%S %Z %Y";

uint64_t text_uint4_hex_read(char u){
  switch(u){
  case '0':
    return 0x0;
  case '1':
    return 0x1;
  case '2':
    return 0x2;
  case '3':
    return 0x3;
  case '4':
    return 0x4;
  case '5':
    return 0x5;
  case '6':
    return 0x6;
  case '7':
    return 0x7;
  case '8':
    return 0x8;
  case '9':
    return 0x9;
  case 'a':
  case 'A':
    return 0xa;
  case 'b':
  case 'B':
    return 0xb;
  case 'c':
  case 'C':
    return 0xc;
  case 'd':
  case 'D':
    return 0xd;
  case 'e':
  case 'E':
    return 0xe;
  case 'f':
  case 'F':
    return 0xf;
  default:
    return text_uint4_hex_read_error;
  }
}
char text_uint4_hex_write(uint64_t m){

  switch(m & 0xF){
  case 0:
    return '0';
  case 1:
    return '1';
  case 2:
    return '2';
  case 3:
    return '3';
  case 4:
    return '4';
  case 5:
    return '5';
  case 6:
    return '6';
  case 7:
    return '7';
  case 8:
    return '8';
  case 9:
    return '9';
  case 10:
    return 'a';
  case 11:
    return 'b';
  case 12:
    return 'c';
  case 13:
    return 'd';
  case 14:
    return 'e';
  case 15:
    return 'f';
  default:
    return text_uint4_hex_write_error;
  }
}
char* text_uint64_hex_read(char* p){
  char ch = *p++;
  if ('0' == ch){
    ch = *p++;
    if ('x' == ch || 'X' == ch){
      /*
       * big endian algorithm
       */
      uint64_t acc_be = 0, ni;
      uint8_t sh = 60, ct = 0;

      do {
        ch = *p++; ct += 1;

        ni = text_uint4_hex_read(ch);

        if (text_uint4_hex_read_error != ni){

          if (0 < sh){

            acc_be |= (ni<<sh);
          }
          else {

            acc_be |= ni;
          }

          if (0 < sh){

            sh -= 4;
          }
          else {

            break;
          }
        }
        else {

          return null; //(punt on user error)
        }
      }
      while (0 != ch && ct <= 16); // 16=(64/4) [nibbles per integer]

      /*
       * host order copy
       */
      uint64_t acc_he = bint_be_to_he64(acc_be);

      char* rem = calloc(1,sizeof(uint64_t));
      {
        memcpy(rem,&acc_he,sizeof(uint64_t));
      }
      return rem;
    }
  }
  return null;
}
char* text_uint64_hex_write(char* mp){
  if (null != mp){

    uint64_t mi_he;
    {
      memcpy(&mi_he,mp,sizeof(uint64_t)); // (portable word alignment handling)
    }
    uint64_t mi_be = bint_he_to_be64(mi_he);      // (big endian algorithm)

    char* res = calloc(19,1); // 19=("0x"+16+null)
    {
      uint64_t ni;
      uint8_t sh = 60;

      char* rz = (res+18);
      char* rp = res;
      *rp++ = '0';
      *rp++ = 'x';
      while (rp < rz){

        ni = ((mi_be>>sh) & 0xF);

        *rp++ = text_uint4_hex_write(ni);

        if (0 < sh){

          sh -= 4;
        }
      }
    }
    return res;
  }
  else {
    return null;
  }
}
char* text_datetime_read(char* txt){
  if (null != txt){

    struct tm bdt;
    
    if (null != strptime(txt,posix_date_format,&bdt)){

      time_t sutc = mktime(&bdt);
      if (-1 != sutc){

        size_t sutc_z = sizeof(time_t);

        char* re = calloc(sutc_z,1);
        /*
         * copy (time_t) to (byte[8]) using [system byte order]
         * 
         * N.B. The data buffer in the malloc memory plane can have a
         * word alignment problem.
         */
        memcpy(re,&sutc,sutc_z);

        return re;
      }
      else {
        char* sr = strerror(errno);

        fprintf(stderr,"text_datetime_read: error from mktime.  %s.\n",sr);
      }
    }
    else {
      char* sr = strerror(errno);

      fprintf(stderr,"text_datetime_read: null result from strptime.  %s.\n",sr);
    }
  }
  else {
    fprintf(stderr,"text_datetime_read: null argument.\n");
  }
  return null;
}
char* text_datetime_write(char* bin){

  if (null != bin){
    /*
     * copy (byte[8]) to (time_t) using [system byte order]
     */
    time_t sutc;
    {
      memcpy(&sutc,bin,sizeof(time_t));
    }
    struct tm sutc_bdt;
    {
      memset(&sutc_bdt,0,sizeof(struct tm));
    }

    localtime_r(&sutc,&sutc_bdt);

    char* cb = calloc(TEXT_DATETIME_BUFZ,1);

    if (0 == strftime(cb,TEXT_DATETIME_BUFZ,posix_date_format,&sutc_bdt)){
      char* sr = strerror(errno);

      fprintf(stderr,"text_datetime_writer: error from strftime.  %s.\n",sr);

      free(cb);

      return null;
    }
    else {
      return cb;
    }
  }
  return null;
}
