CC=gcc

CFLAGS=-Wall -std=c99 -O3 -Wconversion -Wextra -DMAIN_USE_LINKEDLIST_OPTIMIZE=1
RELEASE_BINARY=spellchecker
CFLAGS_DEBUG=-Wall -std=c99 -O0 -g -Wconversion -Wextra -DMAIN_USE_LINKEDLIST_OPTIMIZE=1
DEBUG_BINARY=debug_spellchecker

all: clean-all $(RELEASE_BINARY)
debug: clean-all $(DEBUG_BINARY)

$(RELEASE_BINARY): main.o linkedlist.o spellchecker_util.o
	$(CC) -o $@ $^ $(CFLAGS)

$(DEBUG_BINARY): main.o linkedlist.o spellchecker_util.o
	$(CC) -o $@ $^ $(CFLAGS_DEBUG)

clean:
	rm -f *.o

clean-all: clean
	rm -f $(RELEASE_BINARY) 
	rm -f $(DEBUG_BINARY)
