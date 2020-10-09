
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include "bint.h"
#include "text.h"
/*
 * Little BINT DEMO
 */
int main(int argc, char** argv){

  switch(bint_kind_host()){
  case bint_kind_le:
    printf("HOST BYTE ORDER IS LITTLE ENDIAN\n");
    break;
  case bint_kind_be:
    printf("HOST BYTE ORDER IS BIG ENDIAN\n");
    break;
  default:
    printf("HOST BYTE ORDER IS UNRECOGNIZED\n");
    break;
  }
  /*
   * The TEXT package uses BINT, so the only available DEMO is to just
   * print a host order word.
   */
  uint64_t he64 = 0x0102030405060708;

  char* u_he64 = (char*)(&he64);

  char* u_be64 = text_uint64_hex_write(u_he64);

  printf("BINT BE<64> %s\n",u_be64);

  return 0;
}
