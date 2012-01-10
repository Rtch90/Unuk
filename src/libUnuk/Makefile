CC = g++
CFLAGS = -ansi -Wall -g
LDADD = -lGL -lGLU -lSDL -lSDL_ttf -lSDL_gfx -lSDL_image -ltinyxml
objects = ApplySurface.o Button.o ButtonToggle.o ButtonGroup.o Character.o Collision.o \
	    Debug.o Font.o FPS.o ImageLoader.o IngameMenu.o Input.o MainMenu.o  \
	    Map.o MapElement.o MapEntities.o MemManager.o NPC.o ParticleEmitter.o \
	    Rect.o Text.o Texture.o TextureManager.o Timer.o \
        AStar.o \

.PHONY: default all clean

default: all

%.cpp: %.h

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(objects)

clean:
	rm -f $(objects)
