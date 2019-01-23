using System;

public class LibSaltExample {

  static void Main() {
    Console.WriteLine ("LibSalt Example: ");    
    Examples examples = new Examples();
    examples.Run();
  }    
}

public class Examples {

  private int crypto_sign_PUBLICKEYBYTES = 32;
  private int crypto_sign_SECRETKEYBYTES = 64;

  public void Run() {
    example_randombytes_random();
    example_randombytes_buf(); 
    example_randombytes_buf(); 
    example_randombytes_buf_deterministic();
    example_randombytes_buf_deterministic();
    example_crypto_sign_keypair();
    example_crypto_sign_seed_keypair();
    example_crypto_sign();
  }

  public void example_randombytes_random() {
    Console.WriteLine("Example: randombytes_random()");  
    Console.WriteLine("RandomValue: " + LibSalt.randombytes_random().ToString());
    Console.WriteLine();
  }

  public void example_randombytes_buf() {
    Console.WriteLine("Example: randombytes_buf()");

    int size = 16;
    byte[] buf = new byte[size];
    LibSalt.randombytes_buf(buf);

    Console.WriteLine("Buffer: " + LibSalt.ByteArrayToString(buf));
    Console.WriteLine();
  }

  public void example_randombytes_buf_deterministic() {
    Console.WriteLine("Example: randombytes_buf_deterministic()");

    byte[] buf = new byte[16]; 
    byte[] seed = new byte[] {
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
      0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
      0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
    };

    LibSalt.randombytes_buf_deterministic(buf, seed);
    Console.WriteLine("Buffer: " + LibSalt.ByteArrayToString(buf));
    Console.WriteLine();
  }

  public void example_crypto_sign_keypair() {
    Console.WriteLine("Example: crypto_sign_keypair()");

    byte[] pk = new byte[crypto_sign_PUBLICKEYBYTES];
    byte[] sk = new byte[crypto_sign_SECRETKEYBYTES];
    byte[] pk2 = new byte[crypto_sign_PUBLICKEYBYTES];
    byte[] sk2 = new byte[crypto_sign_SECRETKEYBYTES];
    
    LibSalt.crypto_sign_keypair(pk, sk);
    LibSalt.crypto_sign_keypair(pk2, sk2);

    Console.WriteLine("Keypair One: ");
    Console.WriteLine("pk: " + LibSalt.ByteArrayToString(pk));
    Console.WriteLine("sk: " + LibSalt.ByteArrayToString(sk));

    Console.WriteLine("Keypair Two: ");
    Console.WriteLine("pk: " + LibSalt.ByteArrayToString(pk2));
    Console.WriteLine("sk: " + LibSalt.ByteArrayToString(sk2));
    Console.WriteLine();
  }

  public void example_crypto_sign_seed_keypair() {
    Console.WriteLine("Example: crypto_sign_seed_keypair()");

    byte[] seed = new byte[] {
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
      0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
      0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
    };

    byte[] pk = new byte[crypto_sign_PUBLICKEYBYTES];
    byte[] sk = new byte[crypto_sign_SECRETKEYBYTES];
    byte[] pk2 = new byte[crypto_sign_PUBLICKEYBYTES];
    byte[] sk2 = new byte[crypto_sign_SECRETKEYBYTES];
    
    LibSalt.crypto_sign_seed_keypair(pk, sk, seed);
    LibSalt.crypto_sign_seed_keypair(pk2, sk2, seed);

    Console.WriteLine("Keypair One: ");
    Console.WriteLine("pk: " + LibSalt.ByteArrayToString(pk));
    Console.WriteLine("sk: " + LibSalt.ByteArrayToString(sk));

    Console.WriteLine("Keypair Two: ");
    Console.WriteLine("pk: " + LibSalt.ByteArrayToString(pk2));
    Console.WriteLine("sk: " + LibSalt.ByteArrayToString(sk2));
    Console.WriteLine();
  }

  void example_crypto_sign() { 
    Console.WriteLine("Example: example_crypto_sign()");

    byte[] message = LibSalt.StringToByteArray("example");
    ulong mlen = (ulong) message.Length;

    byte[] pk = new byte[crypto_sign_PUBLICKEYBYTES];
    byte[] sk = new byte[crypto_sign_SECRETKEYBYTES];
    byte[] pk2 = new byte[crypto_sign_PUBLICKEYBYTES];
    byte[] sk2 = new byte[crypto_sign_SECRETKEYBYTES];
    LibSalt.crypto_sign_keypair(pk, sk);
    LibSalt.crypto_sign_keypair(pk2, sk2);

    ulong smlen = (ulong) LibSalt.crypto_sign_BYTES() + mlen;
    byte[] signed_message = new byte[smlen];
    LibSalt.crypto_sign(signed_message, message, mlen, sk);

    Console.WriteLine("Public Key: " + LibSalt.ByteArrayToString(pk));
    Console.WriteLine("Signed Message: " + LibSalt.ByteArrayToString(signed_message)); 

    byte[] unsigned_message = new byte[mlen];
    byte[] unsigned_message2 = new byte[mlen];
    int success = LibSalt.crypto_sign_open(unsigned_message, signed_message, smlen, pk);
    int success2 = LibSalt.crypto_sign_open(unsigned_message2, signed_message, smlen, pk2);  

    Console.WriteLine("Unsigned Message: " + LibSalt.ByteArrayToString(unsigned_message)); 
    Console.WriteLine("Signature Verification for pk: " + LibSalt.ByteArrayToString(pk)); 

    if(success == 0)
      Console.WriteLine("Valid Signature");
    else
      Console.WriteLine("Invalid signature");
    
    Console.WriteLine("Signature Verification for pk2: " + LibSalt.ByteArrayToString(pk2)); 

    if(success2 == 0)
      Console.WriteLine("Valid Signature");
    else
      Console.WriteLine("Invalid signature");
  } 

}
