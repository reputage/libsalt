# makefile for libsalt C# library 
# created by: Michael Mendoza

# -----------------------------------------------------------------------------
# MAKE CONFIGURATION

CC = g++

# complier flags
#  -dynamiclab  turns on generating a dylib for mac
#  -g           adds debugging information to the executable file
#  -Wall        turns on most, but not all, compiler warnings

CFLAGS = -dynamiclib -g -Wall 
TARGET = LibSalt
INCLUDE = -I/usr/local/include/sodium -lsodium 
TESTS = SimpleTest
CXXTEST = -I/usr/local/include/cxxtest

# -----------------------------------------------------------------------------
# LIBRARY FILES

# creates LibSalt dylib binary file
libsalt: 
	$(CC) $(CFLAGS) -o dist/$(TARGET).dylib $(TARGET).cpp $(INCLUDE) 

# builds a C# library dll for LibSalt.cs
build_dll:
	mcs -t:library $(TARGET).cs

# -----------------------------------------------------------------------------
# TESTS

# complies and builds cpp bindings test executable
test_cpp:
	$(CC) -o test/$(TARGET)Test.out test/$(TARGET)Test.cpp $(TARGET).cpp $(INCLUDE)
	./test/$(TARGET)Test.out 

# compiles and builds executable for C# tests with LabSalt.cs 
build_tests:
	mcs test/$(TESTS).cs $(TARGET).cs

# compiles and builds executable for C# tests with LabSalt.dll
build_tests_with_dll:
	mcs test/$(TESTS).cs -r:dist/$(TARGET).dll

# runs C# test
run_tests:
	mono test/$(TESTS).exe

# runs cxxtest (make sure to install cxxtest with `brew install cxxtest`)
tests:
	cxxtestgen --error-printer -o runner.cpp test/$(TARGET)TestSuite.h
	g++ -o runner -I$(CXXTEST) runner.cpp
	./runner
	make clean_tests

# -----------------------------------------------------------------------------
# CLEAN

# clean and removes complied files
clean: 
	rm -f $(TARGET).dylib $(TESTS).exe $(TESTS).dll
	rm -f $(TARGET)Test.out
	rm -f runner runner.cpp

clean_test_cpp:
	rm -f $(TARGET)Test.out

# clean and removes complied files for test runner
clean_testrunner:
	rm -f runner runner.cpp

# Building Wrapper
#g++ -dynamiclib -o libsodium_wrapper.dylib LibSodiumWrapper.cpp -lsodium
#Building Test
#g++ LibSodiumTest.cpp -lsodium LibSodiumWrapper.cpp 