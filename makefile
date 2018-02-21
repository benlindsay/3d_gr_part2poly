CXX = icpc
CXXFLAGS = -O3 -I -Wall -Wshadow -Wstrict-prototypes -Wwrite-strings
LIBS = #-L/home/rrig/Install/fftw3a-threaded/lib -lfftw3_threads -lfftw3 -lpthread
EXECUTABLE=./a.out

SRCS = $(wildcard ./*.cpp)

OBJDIR = objs
OBJS = $(notdir $(SRCS:%.cpp=%.o))

vpath %.cpp ./

all: $(EXECUTABLE)

$(EXECUTABLE):	${OBJS}
	${CXX} ${CXXFLAGS} ${LDFLAGS} -o $@ $^ $(LIBS)

clean:
	rm -f *.o $(EXECUTABLE) 

