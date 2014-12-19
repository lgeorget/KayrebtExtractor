SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
DEPS := $(SRCS:.cpp=.d)
PLUGIN = myplugin
EXEC = $(PLUGIN).so

CXX=g++ #yep, strange but necessary for plugins
CFLAGS=-I/usr/lib/gcc/x86_64-pc-linux-gnu/4.8.3/plugin/include -DNDEBUG -fPIC
CXXFLAGS=$(CFLAGS) -std=c++11
LDFLAGS=-shared

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

run: $(EXEC)
	gcc -iplugindir=. -fplugin=$(PLUGIN) -shared -fPIC -x c -S test.c

%.o: %.cpp
	$(CXX) $< -MM -MF $(patsubst %.cpp,%.d,$<)
	$(CXX) -c $(CXXFLAGS) $< -o $@

.PHONY : clean

clean :
	rm -rf $(OBJS)
	rm -rf $(DEPS)

-include $(wildcard *.d)
