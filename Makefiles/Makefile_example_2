CC=gcc
CFLAGS=-c -g -Wall
LDFLAGS=

SOURCES=bst.c test.c

OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=BST

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	@echo Build :- $(EXECUTABLE)

.c.o:
	@echo Compiling for $@
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o $(EXECUTABLE)
