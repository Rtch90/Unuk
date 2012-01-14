CC = g++
CFLAGS = -ansi -Wall -g
LDADD = -lGL -lGLU -lSDL -lSDL_ttf -lSDL_gfx -lSDL_image -ltinyxml
objects = Button.o ButtonToggle.o ButtonGroup.o Font.o IngameMenu.o \
            MainMenu.o Text.o \

.PHONY: default all clean

default: all

%.cpp: %.h

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(objects)

clean:
	rm -f $(objects)
