CC = g++
CFLAGS = -ansi -Wall -g
LDADD = -lGL -lGLU -lSDL
objects = ApplySurface.o Button.o, ButtonToggle.o Character.o Collision.o \
	    Debug.o FPS.o Font.o ImageLoader.o InGameMenu.o Input.o MainMenu.o  \
	    Map.o MapElement.o MapEntities.o MapTile.o Menu.o NPC.o ParticleEmitter.o \
	    Rect.o Text.o Texture.o TextureManager.o Timer.o \

.PHONY: default all clean

default: all

%.cpp: %.h

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(objects)

clean:
	rm -f $(objects)
