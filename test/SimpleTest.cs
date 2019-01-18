using System.Collections;
using System.Collections.Generic;
using System;
using System.Runtime.InteropServices;


public class SimpleTest {
    
  static void Main() {
    Console.WriteLine ("LibSalt UnitTest.");    
    Start();
  }    

	static void Start () {
		Tests tests = new Tests();
    tests.Test();
    tests.Test2();
    tests.Test3();
	}
	
}

public class Tests {

	public void Test() {
    double tvalue = LibSalt.Add(1.0f, 1.0f);
    Console.WriteLine( tvalue );

    int value = LibSalt.RandInt();
    Console.WriteLine(value);

    int size = 5;
    int[] buf = new int[size];
    LibSalt.FillArray(buf, size);
    Console.WriteLine("Buf Test");

    Console.WriteLine("Buffer Size: " + buf.Length);
    for (int i = 0; i < size; i++)
        Console.WriteLine(buf[i]);
  } 

	public void Test2() {
    Console.WriteLine("LibSodium Test: nacl_randombytes");

    int size = 16;
    byte[] buf = new byte[size];
    LibSalt.nacl_randombytes(buf, size);

    Console.WriteLine("Buffer Size: " + buf.Length);
    Console.WriteLine("Buffer: " + LibSalt.ByteArrayToString(buf));
  } 

	public void Test3() {
    Console.WriteLine("LibSodium Test: randombytes_buf_deterministic");

    int size = 16;
    byte[] buf = new byte[size];
    byte[] seed = new byte[] {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
        0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
        0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
      };
    LibSalt.nacl_randombytes_buf_deterministic(buf, size, seed);

    Console.WriteLine("Buffer Size: " + buf.Length);
    Console.WriteLine("Buffer: " + LibSalt.ByteArrayToString(buf));
  } 
}