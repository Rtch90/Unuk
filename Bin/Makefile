CC = g++
CFLAGS = -ansi -Wall -g
LDADD = -lGL -lGLU  -lglut -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf -ltinyxml
LDADDSTATIC = -Wl,-Bstatic -lSDL -lSDL_image -lopenal -lalut -L/usr/X11 -Wl,-Bdynamic -lasound -lartsc -lesd -lpulse -lpulse-simple -ldirectfb -lvga -laa -lcaca -ljpeg -ltiff -

.PHONY: default static all clean

default: all

all:
	$(MAKE) -C ../src/libUnuk
	$(MAKE) -C ../src/Unuk
	$(CC) $(CFLAGS) -o Unuk ../src/Unuk/main.cpp ../src/libUnuk/*.o ../src/Unuk/*.o $(LDADD)

static:
	@echo -e "\033[1;31mThis is an experimental build, if it does not work, don't complain...\033[0m"
	@sleep 1
	$(MAKE) -C ../src/libUnuk
	$(MAKE) -C ../src/Unuk
	$(CC) $(CFLAGS) -o build/Unuk-static ../src/Unuk/main.cpp ../src/libUnuk/*.o ../src/Unuk/*.o $(LDADDSTATIC)

clean:
	$(MAKE) -C ../src/libUnuk clean
	$(MAKE) -C ../src/Unuk clean
	rm -f Unuk Debug.log ../Data/Debug.log ../Unuk-QT/Unuk-QT
