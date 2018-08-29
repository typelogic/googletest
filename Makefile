
# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread

all : testapp

sample1.o : sample1.cc sample1.h 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c sample1.cc

testapp : sample1.o testapp.cc libgtest.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

# no -fPIC works?
gtest-all.o : src/*.cc src/*.h include/gtest/*.h include/gtest/internal/*.h
	$(CXX) $(CPPFLAGS) -I. $(CXXFLAGS) -c src/gtest-all.cc

# static library
libgtest.a: gtest-all.o
	ar rcs libgtest.a gtest-all.o

# dynamic library
libgtest.so: gtest-all.o
	$(CXX) -shared gtest-all.o -o libgtest.so

clean:
	@rm -f *.o *.exe *.a *.so *.dll
