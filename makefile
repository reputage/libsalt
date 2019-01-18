
CC = g++

# complier flags
# -dynamiclab   turns on generating a dylib for mac
#  -g           adds debugging information to the executable file
#  -Wall        turns on most, but not all, compiler warnings
CFLAGS = -dynamiclib -g -Wall 
TARGET = LibSalt
TESTS = SimpleTest

libsalt: 
	$(CC) $(CFLAGS) -o $(TARGET).dylib $(TARGET).cpp -lsodium

test_cpp:
	$(CC) $(TARGET)Test.cpp -lsodium $(TARGET).cpp

build_tests:
	mcs $(TESTS).cs $(TARGET).cs

run_tests:
	mono $(TESTS).exe

clean: 
	rm -f $(TARGET).dylib $(TESTS).exe
	