TARGET  := pixelStencil 
SRCS    := PixelStencil.cpp
OBJS    := ${SRCS:.cpp=.o} 
DEPS    := ${SRCS:.cpp=.dep} 
    
CXXFLAGS = -std=c++0x -pedantic -Wall -I /usr/X11/include/
LDFLAGS = -L/usr/X11/lib/
LIBS    = -lX11 -lpthread

.PHONY: all clean distclean 

all: release

release: ${TARGET}

${TARGET}: ${OBJS} 
	${CXX} ${LDFLAGS} -o $@ $^ ${LIBS} 

${OBJS}: %.o: %.cpp %.dep 
	${CXX} ${CXXFLAGS} -o $@ -c $< 

${DEPS}: %.dep: %.cpp Makefile 
	${CXX} ${CXXFLAGS} -MM $< > $@ 

clean:
	rm -f *~ *.o ${TARGET} 

distclean: clean

