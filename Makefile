CPP_FILES+= $(wildcard src/*.cpp)
OBJECTS = $(CPP_FILES:.cpp=.o)  #find the associated o-filenames
CXXFLAGS = -std=c++1y -I matgui/include/matgui -g -Iinclude
LIBS = matgui/matgui-sdl.a -lSDL2 -lGL -lSDL2_ttf -lSDL2_image

TARGET = map-broadphase

all: ${TARGET} .depend

${TARGET}: ${OBJECTS}
	${CXX} ${CXXFLAGS} -o ${TARGET} ${OBJECTS} ${LIBS}

#rule for calculate dependencies
.depend: ${CPP_FILES} Makefile
	git submodule update --init
	make -C matmake/
	@echo
	@echo Calculating dependencies
	matmake/matdep ${CPP_FILES} ${CXXFLAGS} > .depend
	
#include the dependencies
include .depend

clean:
	rm ${OBJECTS}
