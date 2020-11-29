
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include "bint.h"

/*
 * Tiny BINT DEMO
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
   * Trivial byte order dump
   */
  uint64_t he64 = 0x0102030405060708;

  uint8_t* he64p = (uint8_t*)(&he64);

  printf("BINT HE<64> 0x%lX\n",he64);
  {
    off_t bc = 0;
    size_t bz = 8;
    for (; bc < bz; bc++){

      printf("BINT HE<64> [%ld] 0x%0x\n", bc, he64p[bc]);
    }
  }

  return 0;
}
