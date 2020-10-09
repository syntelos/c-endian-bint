
The program prep/bint produces a compiler command line define for
endianness.  One of

  -DBINT_KIND=BINT_KIND_LE

or

  -DBINT_KIND=BINT_KIND_BE

This is employed by

  inc/bint.h

and therefore

  src/bint.c

which (combined) is the endian byte order swap package for 16, 32, and
64 bit integer words.

The bint package interface is "bint_swap_be" for 16, 32, and 64 bit
cases.  The

  bint_swap_be<N>

interface serves both

  he_to_be<N>

(host endian to big endian) and

  be_to_he<N>

(big endian to host endian) roles because the code definition body of
both are identical.

Whereever one of

  he_to_be<N>

or

  be_to_he<N>

is needed, the

  bint_swap_be<N>

is employed.

However, bint user code is encouraged to employ

  bint_he_to_be<N>

and

  bint_be_to_he<N>

(where <N> is one of 16, 32, or 64) for notational completeness.
These macros perform the semantics representated here.

