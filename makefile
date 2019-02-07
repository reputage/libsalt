# makefile for libsalt C# library 
# created by: Michael Mendoza

# -----------------------------------------------------------------------------
# MAKE CONFIGURATION

CC = g++

# complier flags
#  -dynamiclab  turns on generating a dylib for mac
#  -g           adds debugging information to the executable file
#  -Wall        turns on most, but not all, compiler warnings

CFLAGS = -dynamiclib -Wall 
TARGET = LibSalt
INCLUDE = -I/usr/local/include/sodium -lsodium -I/libsalt
TESTS = LibSaltTest
CXXTEST = -I/usr/local/include/cxxtest

# -----------------------------------------------------------------------------
# LIBRARY FILES

# creates LibSalt dylib binary file (LibSalt.dylib) and C# dll (LibSalt.dll)
build: 
	mkdir -p dist
	cp libsalt/$(TARGET).cs dist/$(TARGET).cs 
	$(CC) $(CFLAGS) -o dist/$(TARGET).dylib libsalt/$(TARGET).cpp $(INCLUDE) 
	mcs -t:library dist/$(TARGET).cs

# -----------------------------------------------------------------------------
# EXAMPLES

# complies and builds c# bindings examples
example: 
	mcs examples/$(TARGET)Example.cs dist/$(TARGET).cs
	mono examples/$(TARGET)Example.exe

# complies and builds cpp bindings examples
example_cpp:
	$(CC) -o examples/$(TARGET)Example.out examples/$(TARGET)Example.cpp libsalt/$(TARGET).cpp $(INCLUDE)
	./examples/$(TARGET)Example.out 
	make clean_examples

# -----------------------------------------------------------------------------
# TESTS

# runs C# unit tests
tests:
	mcs test/$(TESTS).cs dist/$(TARGET).cs
	mono test/$(TARGET)Test.exe 
	make clean_tests

# runs cxxtest (make sure to install cxxtest with `brew install cxxtest`)
tests_cpp:
	cxxtestgen --error-printer -o runner.cpp test/$(TARGET)TestSuite.h 
	g++ -o runner runner.cpp libsalt/$(TARGET).cpp $(CXXTEST) $(INCLUDE) 
	./runner
	make clean_tests

# compiles and builds executable for C# tests with LabSalt.cs 
build_tests:
	mcs test/$(TESTS).cs dist/$(TARGET).cs

# compiles and builds executable for C# tests with LabSalt.dll
build_tests_dll:
	mcs test/$(TESTS).cs -r:dist/$(TARGET).dll

# -----------------------------------------------------------------------------
# CLEAN

# clean and removes complied files
clean: 
	rm -f dist/$(TARGET).dylib dist/$(TARGET).dll 
	rm -fr dist/$(TARGET).dylib.dSYM
	rm -f dist/$(TARGET).cs
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