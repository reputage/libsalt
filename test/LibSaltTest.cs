using System.Collections;
using System.Collections.Generic;
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;


public class LibSaltTest {

  static void Main() {
    Console.WriteLine ("LibSalt UnitTest.");    
    RunUnitTests();
  }    

	static void RunUnitTests () {
		
    Tests tests = new Tests();
    tests.run_unit_tests();
	}
}

public class UnitTest {

  static public void ASSERT_EQUALS(float x, float y) {
    bool equals = x == y;

    if(equals)
      Console.WriteLine(".. OK ..");
    else 
      Console.WriteLine("Error: Expected " + x.ToString() + " == " + y.ToString());
  }
  
  static public void ASSERT_DIFFERS(float x, float y) {
    bool differs = x != y;

    if(differs)
      Console.WriteLine(".. OK ..");
    else 
      Console.WriteLine("Error: Expected " + x.ToString() + " != " + y.ToString());
  }

  static public void ASSERT_SAME_DATA(byte[] x, byte[] y) {
    bool isSame = true;
    for(int i = 0; i < x.Length; i++)
      isSame = (x[i] == y[i]) ? isSame : false;
  
    if(isSame)
      Console.WriteLine(".. OK ..");
    else {
      String x_str = LibSalt.ByteArrayToString(x);
      String y_str = LibSalt.ByteArrayToString(y);
      Console.WriteLine("Error: Expected " + x_str + " == " + y_str);
    } 
  } 

  static public void ASSERT_DIFFERENT_DATA(byte[] x, byte[] y) {
    bool isDifferent = false;
    for(int i = 0; i < x.Length; i++)
      isDifferent = (x[i] == y[i]) ? isDifferent : true;

    if(isDifferent)
      Console.WriteLine(".. OK ..");
    else {
      String x_str = LibSalt.ByteArrayToString(x);
      String y_str = LibSalt.ByteArrayToString(y);
      Console.WriteLine("Error: Expected " + x_str + " != " + y_str);
    }
  }
}

public class Tests {

  private int crypto_sign_PUBLICKEYBYTES = 32;
  private int crypto_sign_SECRETKEYBYTES = 64;

  private byte[] seed = new byte[] {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
        0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
        0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
      };

  private byte[] seed2 = new byte[] {
        0x01, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
        0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
        0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
      };

  public void run_unit_tests() {
    Console.WriteLine("Running c# test tests (7 tests)");

    Stopwatch stopwatch = new Stopwatch();
    stopwatch.Start(); 

    test_randombytes_random();
    test_randombytes_buf();
    test_randombytes_buf_deterministic();
    test_crypto_sign_keypair();
    test_crypto_sign_seed_keypair();
    test_crypto_sign();
    test_crypto_sign_open();

    stopwatch.Stop(); 

    Console.WriteLine("Ran 7 tests in " + stopwatch.ElapsedMilliseconds.ToString() + " ms");
  }

  public void test_randombytes_random() {
    Console.WriteLine("Testing randombytes_random() .....");
    
    UnitTest.ASSERT_DIFFERS(LibSalt.randombytes_random(), LibSalt.randombytes_random());
  }

  public void test_randombytes_buf() { 
    Console.WriteLine("Testing randombytes_buf() .....");

    int size = 16;
    byte[] buf = new byte[size];
    byte[] buf2 = new byte[size];

    LibSalt.randombytes_buf(buf);
    LibSalt.randombytes_buf(buf2);

    UnitTest.ASSERT_DIFFERENT_DATA(buf, buf2);
  }

  public void test_randombytes_buf_deterministic() {
    Console.WriteLine("Testing randombytes_buf_deterministic() .....");

    int size = 16;
    byte[] buf = new byte[size];
    byte[] buf2 = new byte[size];
    byte[] buf3 = new byte[size];
    LibSalt.randombytes_buf_deterministic(buf, seed);
    LibSalt.randombytes_buf_deterministic(buf2, seed);
    LibSalt.randombytes_buf_deterministic(buf3, seed2);
    
    // Test for generating same randombyte arrays with same seeds
    UnitTest.ASSERT_SAME_DATA(buf, buf2); 

    // Test for generating different randombyte arrays with different seeds
    UnitTest.ASSERT_DIFFERENT_DATA(buf, buf3);
    UnitTest.ASSERT_DIFFERENT_DATA(buf2, buf3); 
  }

  public void test_crypto_sign_keypair() {
    Console.WriteLine("Testing crypto_sign_keypair() .....");

    byte[] pk = new byte[crypto_sign_PUBLICKEYBYTES];
    byte[] sk = new byte[crypto_sign_SECRETKEYBYTES];
    byte[] pk2 = new byte[crypto_sign_PUBLICKEYBYTES];
    byte[] sk2 = new byte[crypto_sign_SECRETKEYBYTES];
    LibSalt.crypto_sign_keypair(pk, sk);
    LibSalt.crypto_sign_keypair(pk2, sk2);

    // Test for proper pk and sk array sizes
    UnitTest.ASSERT_EQUALS(pk.Length, crypto_sign_PUBLICKEYBYTES);
    UnitTest.ASSERT_EQUALS(sk.Length, crypto_sign_SECRETKEYBYTES);

    // Test for generating different random pk/sk  
    UnitTest.ASSERT_DIFFERENT_DATA(pk, pk2);
    UnitTest.ASSERT_DIFFERENT_DATA(sk, sk2);
  }

  public void test_crypto_sign_seed_keypair() {
    Console.WriteLine("Testing crypto_sign_seed_keypair() .....");

    byte[] pk = new byte[crypto_sign_PUBLICKEYBYTES];
    byte[] sk = new byte[crypto_sign_SECRETKEYBYTES];
    byte[] pk2 = new byte[crypto_sign_PUBLICKEYBYTES];
    byte[] sk2 = new byte[crypto_sign_SECRETKEYBYTES];
    LibSalt.crypto_sign_seed_keypair(pk, sk, seed);
    LibSalt.crypto_sign_seed_keypair(pk2, sk2, seed);

    // Test for proper pk and sk array sizes
    UnitTest.ASSERT_EQUALS(pk.Length, crypto_sign_PUBLICKEYBYTES);
    UnitTest.ASSERT_EQUALS(sk.Length, crypto_sign_SECRETKEYBYTES);

    // Test for generating same pk/sk for same seed
    UnitTest.ASSERT_SAME_DATA(pk, pk2);
    UnitTest.ASSERT_SAME_DATA(sk, sk2);
  }

  public void test_crypto_sign() {
    Console.WriteLine("Testing crypto_sign() .....");

    byte[] message = LibSalt.StringToByteArray("test");
    ulong mlen = 4; 
    byte[] pk = new byte[crypto_sign_PUBLICKEYBYTES];
    byte[] sk = new byte[crypto_sign_SECRETKEYBYTES];
    byte[] pk2 = new byte[crypto_sign_PUBLICKEYBYTES];
    byte[] sk2 = new byte[crypto_sign_SECRETKEYBYTES];

    LibSalt.crypto_sign_keypair(pk, sk);
    LibSalt.crypto_sign_keypair(pk2, sk2);

    ulong smlen = (ulong) LibSalt.crypto_sign_BYTES() + (ulong) mlen;
    byte[] signed_message = new byte[smlen];
    byte[] signed_message2 = new byte[smlen];

    LibSalt.crypto_sign(signed_message, message, mlen, sk);
    LibSalt.crypto_sign(signed_message2, message, mlen, sk);

    // Test for proper signed message 
    UnitTest.ASSERT_SAME_DATA(signed_message, signed_message2);
  }

  void test_crypto_sign_open() {
    Console.WriteLine("Testing crypto_sign_open() .....");

    byte[] message = LibSalt.StringToByteArray("test");
    ulong mlen = 4; 

    byte[] pk = new byte[crypto_sign_PUBLICKEYBYTES];
    byte[] sk = new byte[crypto_sign_SECRETKEYBYTES];
    byte[] pk2 = new byte[crypto_sign_PUBLICKEYBYTES];
    byte[] sk2 = new byte[crypto_sign_SECRETKEYBYTES];
    LibSalt.crypto_sign_keypair(pk, sk);
    LibSalt.crypto_sign_keypair(pk2, sk2);

    ulong smlen = (ulong) LibSalt.crypto_sign_BYTES() + mlen;
    byte[] signed_message = new byte[smlen];
    LibSalt.crypto_sign(signed_message, message, mlen, sk);

    byte[] unsigned_message = new byte[mlen];
    int success = LibSalt.crypto_sign_open(unsigned_message, signed_message, smlen, pk);
    int success2 = LibSalt.crypto_sign_open(unsigned_message, signed_message, smlen, pk2);

    // Test for sucessful decoding signed message with correct private key
    UnitTest.ASSERT_EQUALS(success, 0);

    // Test for unsucessful decoding signed message with incorrect private key
    UnitTest.ASSERT_DIFFERS(success2, 0);
  }

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
}