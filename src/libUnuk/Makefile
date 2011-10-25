CC = g++
CFLAGS = -ansi -Wall -g
LDADD = -lGL -lGLU -lSDL
objects = Debug.o Entity.o ImageLoader.o Sprite.o Input.o \

.PHONY: default all clean

default: all

%.cpp: %.h

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(objects)

clean:
	rm -f $(objects)
