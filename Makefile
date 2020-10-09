#
# COMPILER
#
CC := clang
#
# REPRESENTATION [600] SUSv3 / UNIX 03 / POSIX.1-2001
#
PORTABILITY := -D_XOPEN_SOURCE=600
#
# CONSISTENCY
#
WARNINGS := #-Wno-long-long -Wall -pedantic -Werror
#
# INSPECTION
#
DEBUG := -g -ggdb
#
# STRUCTURE
#
CCFLAGS := $(PORTABILITY) -Iinc $(WARNINGS) $(DEBUG)

LDFLAGS := #-lpthread
#
# DEPENDENCIES
#
HEADERS := inc/*.h

SOURCES := src/*.c

bint: prep/bint $(HEADERS) $(SOURCES) bint.c
	$(CC) $(shell prep/bint) $(CCFLAGS) -o $@ $(SOURCES) bint.c $(LDFLAGS)

prep/bint: prep/bint.c
	$(CC) -o prep/bint prep/bint.c

clean:
	rm -f prep/bint bint core

