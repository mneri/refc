CC=gcc
CCFLAGS=-Wall -pedantic -O2
LIBNAME=librefc.a

all: $(LIBNAME)

clean:
	rm -f $(LIBNAME) *.o

$(LIBNAME): refc.o
	ar rcs librefc.a refc.o

refc.o: refc.c refc.h
	$(CC) $(CCFLAGS) -c refc.c -o refc.o
