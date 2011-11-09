LIBS += -lGL \
    -lSDL \
    -lSDL_ttf \
    -lSDL_image \
    -lGLU
RESOURCES += 
OTHER_FILES += ../src/libUnuk/Debug.o
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
    ../src/libUnuk/Texture.h
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
    ../src/libUnuk/Texture.cpp
