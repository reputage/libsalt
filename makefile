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
TESTS = LabSaltTest
CXXTEST = -I/usr/local/include/cxxtest

# -----------------------------------------------------------------------------
# LIBRARY FILES

# creates LibSalt dylib binary file (LibSalt.dylib)
libsalt: 
	$(CC) $(CFLAGS) -o dist/$(TARGET).dylib $(TARGET).cpp $(INCLUDE) 

# builds a C# library dll for LibSalt.cs (LibSalt.dll)
build_dll:
	mcs -t:library $(TARGET).cs

# -----------------------------------------------------------------------------
# EXAMPLES
# complies and builds cpp bindings test executable
example:
	$(CC) -o examples/$(TARGET)Example.out examples/$(TARGET)Example.cpp $(TARGET).cpp $(INCLUDE)
	./examples/$(TARGET)Example.out 

# -----------------------------------------------------------------------------
# TESTS

tests:
	make tests_cpp
	make tests_cs
	make clean_tests

# runs cxxtest (make sure to install cxxtest with `brew install cxxtest`)
tests_cpp:
	cxxtestgen --error-printer -o runner.cpp test/$(TARGET)TestSuite.h 
	g++ -o runner runner.cpp $(CXXTEST) $(TARGET).cpp $(INCLUDE) 
	./runner

# runs C# test
tests_cs:
	mcs test/$(TESTS).cs $(TARGET).cs
	mono test/$(TESTS).exe

# compiles and builds executable for C# tests with LabSalt.cs 
build_tests_cs:
	mcs test/$(TESTS).cs $(TARGET).cs

# compiles and builds executable for C# tests with LabSalt.dll
build_tests_cs_with_dll:
	mcs test/$(TESTS).cs -r:dist/$(TARGET).dll

# -----------------------------------------------------------------------------
# CLEAN

# clean and removes complied files
clean: 
	rm -f dist/$(TARGET).dylib dist/$(TESTS).dll
	rm -f examples/*.out examples/*.exe
	rm -f test/*.out test/*.exe
	rm -f runner runner.cpp

# clean and removes complied files for test runner
clean_tests:
	rm -f test/*.exe
	rm -f runner runner.cpp

# Building Wrapper
#g++ -dynamiclib -o libsodium_wrapper.dylib LibSodiumWrapper.cpp -lsodium
#Building Test
#g++ LibSodiumTest.cpp -lsodium LibSodiumWrapper.cpp 