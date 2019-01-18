
CC = g++

# complier flags
# -dynamiclab   turns on generating a dylib for mac
#  -g           adds debugging information to the executable file
#  -Wall        turns on most, but not all, compiler warnings
CFLAGS = -dynamiclib -g -Wall 
TARGET = LibSalt
INCLUDE = -I/include -lsodium
TESTS = SimpleTest

libsalt: 
	$(CC) $(CFLAGS) -o dist/$(TARGET).dylib $(TARGET).cpp $(INCLUDE) 

test_cpp:
	$(CC) $(TARGET)Test.cpp -lsodium $(TARGET).cpp

build_tests:
	mcs $(TESTS).cs $(TARGET).cs

run_tests:
	mono $(TESTS).exe

clean: 
	rm -f $(TARGET).dylib $(TESTS).exe
	
# Building Wrapper
#g++ -dynamiclib -o libsodium_wrapper.dylib LibSodiumWrapper.cpp -lsodium
#Building Test
#g++ LibSodiumTest.cpp -lsodium LibSodiumWrapper.cpp 
