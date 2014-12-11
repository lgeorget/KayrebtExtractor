SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
PLUGIN = myplugin
EXEC = $(PLUGIN).so

CXX=g++ #yep, strange but necessary for plugins
CFLAGS=-I/usr/lib/gcc/x86_64-pc-linux-gnu/4.8.3/plugin/include -fPIC
CXXFLAGS=$(CFLAGS)
LDFLAGS=-shared

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

run: $(EXEC)
	gcc -iplugindir=. -fplugin=$(PLUGIN) -shared -fPIC -x c -S test.c
