AR      = ar
RANLIB  = ranlib
CC      = gcc
CFLAGS 	= -D_GNU_SOURCE=1 -ggdb -Wall -Wmissing-declarations -Wshadow -Wstrict-prototypes -Wmissing-prototypes -Wpointer-arith -Wcast-qual -Wsign-compare -Wpedantic -fPIC
INCPATH	= -I. -I/usr/local/include -I../lib-basics
LINK	= gcc
LFLAGS	= -L/usr/local/lib/ -L../lib-basics
LIBS	= -lbasics

.SUFFIXES:	.o .c

HEADERS = 
SOURCES_CMP = stl-cmp.c
OBJECTS_CMP = stl-cmp.o
EXE_CMP = stl-cmp

SOURCES_DUMP = stl-dump.c
OBJECTS_DUMP = stl-dump.o
EXE_DUMP = stl-dump

SOURCES_POLYHEDRON = stl-polyhedron.c
OBJECTS_POLYHEDRON = stl-polyhedron.o
EXE_POLYHEDRON = stl-polyhedron

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

all: $(EXE_CMP) $(EXE_DUMP) $(EXE_POLYHEDRON)

$(EXE_CMP): $(OBJECTS_CMP)
	$(LINK) $(LFLAGS) -o $(EXE_CMP) $(OBJECTS_CMP) $(LIBS)

$(EXE_DUMP): $(OBJECTS_DUMP)
	$(LINK) $(LFLAGS) -o $(EXE_DUMP) $(OBJECTS_DUMP) $(LIBS)

$(EXE_POLYHEDRON): $(OBJECTS_POLYHEDRON)
	$(LINK) $(LFLAGS) -o $(EXE_POLYHEDRON) $(OBJECTS_POLYHEDRON) $(LIBS)

clean:
	rm -f $(OBJECTS_DUMP) $(OBJECTS_CMP) $(OBJECTS_POLYHEDRON) $(EXE_CMP) $(EXE_DUMP) $(EXE_POLYHEDRON) *~ *.bin


