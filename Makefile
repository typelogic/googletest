
# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread

all : testapp

sample1.o : sample1.cc sample1.h 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c sample1.cc

# can also use libgtest.so
#testapp : sample1.o testapp.cc libgtest.so
#testapp : sample1.o testapp.cc libgtest.a
testapp : sample1.o testapp.cc gmock.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

mytestapp : mytestapp.cpp gmock.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

mocktest : mocktest.cpp gmock.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -Igooglemock -Igooglemock/include $^ -o $@

mockey : mockey.cpp gmock.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -Igooglemock -Igooglemock/include $^ -o $@

testapp2: testapp2.cc gmock.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -Igooglemock/include/ -o $@ $^

# no -fPIC works?
gtest-all.o : src/*.cc src/*.h include/gtest/*.h include/gtest/internal/*.h
	$(CXX) $(CPPFLAGS) -I. $(CXXFLAGS) -c src/gtest-all.cc

# static library
libgtest.a: gtest-all.o
	ar rcs libgtest.a gtest-all.o

# dynamic library
libgtest.so: gtest-all.o
	$(CXX) -shared gtest-all.o -o libgtest.so

gmock-all.o : googlemock/src/*.cc googlemock/include/gmock/*.h googlemock/include/gmock/internal/*.h 
	$(CXX) $(CPPFLAGS) -Igooglemock -Igooglemock/include $(CXXFLAGS) -c googlemock/src/gmock-all.cc

# combines both gtest and gmock into one static library
gmock.a : gmock-all.o gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

clean:
	@rm -f *.o *.exe *.a *.so *.dll
