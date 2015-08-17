CXXFLAGS=-g -O3 -flto -Wall -std=c++11

all: libpintoolhooks

libpintoolhooks: libpintoolhooks.so

libpintoolhooks.a: pintool_hooks.o
	$(AR) rcsv $@ $<

libpintoolhooks.so: pintool_hooks.o
	$(CXX) -shared -o $@ $<

pintool_hooks.o: pintool_hooks.cpp pintool_hooks.h
	$(CXX) $(CXXFLAGS) $< -c -o $@ -fPIC -DPIC

clean:
	$(RM) *~ *.o *.a *.so
