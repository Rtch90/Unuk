LIBS += -lGL \
    -lSDL \
    -lSDL_ttf \
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
    ../src/Unuk/Constants.h
SOURCES += ../src/libUnuk/Debug.cpp \
    ../src/Unuk/main.cpp \
    ../src/libUnuk/Input.cpp \
    ../src/libUnuk/Timer.cpp \
    ../src/libUnuk/Font.cpp
