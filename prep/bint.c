/*
 * Produce compiler command line define for endianness.
 */
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
/*
 * https://sourceforge.net/p/predef/wiki/Endianness/
 */
typedef enum bint_kind {
  /*
   * The endianness is unknown.  The conversion functions will return
   * zero.  (Note that "middle endian" cases are believed to be
   * archaic and have not been handled).
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

/*
 * Determine host system endianness dynamically.
 */

#define bint_host_sys_undefined 0xF

static bint_kind bint_host_sys = bint_host_sys_undefined;

int main(int argc, char** argv){

  bint16_t test;
  {
    test.data[0] = 0x01;
    test.data[1] = 0x00;
  }

  switch (test.value){
  case 0x0100U:
    bint_host_sys = bint_kind_be;
    break;
  case 0x0001U:
    bint_host_sys = bint_kind_le;
    break;
  default:
    bint_host_sys = bint_kind_un;
    break;
  }

  if (bint_kind_le == bint_host_sys){

    printf("-DBINT_KIND=BINT_KIND_LE");
    return 0;
  }
  else if (bint_kind_be == bint_host_sys){

    printf("-DBINT_KIND=BINT_KIND_BE");
    return 0;
  }
  else {
    return 1;
  }
}
