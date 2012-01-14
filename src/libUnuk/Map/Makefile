CC = g++
CFLAGS = -ansi -Wall -g
LDADD = -lGL -lGLU -lSDL -lSDL_ttf -lSDL_gfx -lSDL_image -ltinyxml
objects = Map.o MapElement.o MapEntities.o  \

.PHONY: default all clean

default: all

%.cpp: %.h

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(objects)

clean:
	rm -f $(objects)
