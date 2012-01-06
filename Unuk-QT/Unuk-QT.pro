LIBS += -lGL \
    -lSDL \
    -lSDL_ttf \
    -lSDL_image \
    -lSDL_gfx \
    -ltinyxml \
    -lGLU
RESOURCES += 
OTHER_FILES += ../src/libUnuk/Debug.o \
    ../Data/Media/Maps/map
HEADERS += ../src/libUnuk/Debug.h \
    ../src/Libs/wglext.h \
    ../src/Libs/glxext.h \
    ../src/libUnuk/Input.h \
    ../src/libUnuk/Rect.h \
    ../src/libUnuk/Timer.h \
    ../src/libUnuk/Font.h \
    ../Constants.h \
    ../src/Unuk/Constants.h \
    ../src/libUnuk/ApplySurface.h \
    ../src/Unuk/Globals.h \
    ../src/libUnuk/ImageLoader.h \
    ../src/libUnuk/TextureManager.h \
    ../src/libUnuk/Texture.h \
    ../src/libUnuk/Text.h \
    ../src/libUnuk/MapTile.h \
    ../src/libUnuk/Map.h \
    ../src/libUnuk/Button.h \
    ../src/libUnuk/ButtonToggle.h \
    ../src/libUnuk/MainMenu.h \
    ../src/libUnuk/ParticleEmitter.h \
    ../src/libUnuk/IngameMenu.h \
    ../src/libUnuk/Collision.h \
    ../src/libUnuk/Character.h \
    ../src/libUnuk/NPC.h \
    ../src/Unuk/Player.h \
    ../src/Unuk/Game.h \
    ../src/libUnuk/MapElement.h \
    ../src/libUnuk/MapEntities.h \
    ../src/libUnuk/FPS.h \
    ../src/libUnuk/MemManager.h \
    ../src/libUnuk/MemClass.h \
    ../src/libUnuk/Node.h
SOURCES += ../src/libUnuk/Debug.cpp \
    ../src/Unuk/main.cpp \
    ../src/libUnuk/Input.cpp \
    ../src/libUnuk/Timer.cpp \
    ../src/libUnuk/Font.cpp \
    ../src/libUnuk/ApplySurface.cpp \
    ../src/Unuk/Globals.cpp \
    ../src/libUnuk/Rect.cpp \
    ../src/libUnuk/ImageLoader.cpp \
    ../src/libUnuk/TextureManager.cpp \
    ../src/libUnuk/Texture.cpp \
    ../src/libUnuk/Text.cpp \
    ../src/libUnuk/Map.cpp \
    ../src/libUnuk/Button.cpp \
    ../src/libUnuk/ButtonToggle.cpp \
    ../src/libUnuk/ParticleEmitter.cpp \
    ../src/libUnuk/MainMenu.cpp \
    ../src/libUnuk/IngameMenu.cpp \
    ../src/libUnuk/Collision.cpp \
    ../src/libUnuk/Character.cpp \
    ../src/libUnuk/NPC.cpp \
    ../src/Unuk/Player.cpp \
    ../src/Unuk/Game.cpp \
    ../src/libUnuk/MapElement.cpp \
    ../src/libUnuk/MapEntities.cpp \
    ../src/libUnuk/FPS.cpp \
    ../src/libUnuk/MemManager.cpp
