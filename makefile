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
INCLUDE = -I/usr/local/include/sodium -lsodium -I/libsalt
TESTS = LabSaltTest 
CXXTEST = -I/usr/local/include/cxxtest

# -----------------------------------------------------------------------------
# LIBRARY FILES

# creates LibSalt dylib binary file (LibSalt.dylib) and C# dll (LibSalt.dll)
build: 
	$(CC) $(CFLAGS) -o dist/$(TARGET).dylib libsalt/$(TARGET).cpp $(INCLUDE) 
	mcs -t:library libsalt/$(TARGET).cs
	mv libsalt/$(TARGET).dll dist/$(TARGET).dll

# -----------------------------------------------------------------------------
# EXAMPLES

# complies and builds c# bindings examples
example:
	mcs examples/$(TARGET)Example.cs ./libsalt/$(TARGET).cs
	mono examples/$(TARGET)Example.exe

# complies and builds cpp bindings examples
example_cpp:
	$(CC) -o examples/$(TARGET)Example.out examples/$(TARGET)Example.cpp libsalt/$(TARGET).cpp $(INCLUDE)
	./examples/$(TARGET)Example.out 
	make clean_examples

# -----------------------------------------------------------------------------
# TESTS

tests:
	make tests_cpp
	make tests_cs
	make clean_tests

# runs cxxtest (make sure to install cxxtest with `brew install cxxtest`)
tests_cpp:
	cxxtestgen --error-printer -o runner.cpp test/$(TARGET)TestSuite.h 
	g++ -o runner runner.cpp libsalt/$(TARGET).cpp $(CXXTEST) $(INCLUDE) 
	./runner

# runs C# unit tests
tests_cs:
	mcs test/$(TARGET)Test.cs ./libsalt/$(TARGET).cs
	mono test/$(TARGET)Test.exe

# compiles and builds executable for C# tests with LabSalt.cs 
build_tests_cs:
	mcs test/$(TESTS).cs libsalt/$(TARGET).cs

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

# clean and removes complied files for examples 
clean_examples:
	rm -f examples/*.out

# clean and removes complied files for test runner
clean_tests:
	rm -f test/*.exe
	rm -f runner runner.cpp

# Building Wrapper
#g++ -dynamiclib -o libsodium_wrapper.dylib LibSodiumWrapper.cpp -lsodium
#Building Test
#g++ LibSodiumTest.cpp -lsodium LibSodiumWrapper.cpp 