using System.Collections;
using System.Collections.Generic;
using System;
using System.Text;
using System.Runtime.InteropServices;

public class LibSalt {

  public static string ByteArrayToString(byte[] ba) {
    return BitConverter.ToString(ba).Replace("-", "");
  } 

  public static byte[] StringToByteArray(string str) {
    return Encoding.ASCII.GetBytes(str);
  }

  [DllImport("dist/simplemath.dylib")]
  public static extern int RandInt();

  [DllImport("dist/simplemath.dylib")]
  public static extern double Add(double a, double b);

  [DllImport("dist/simplemath.dylib")]
  public static extern void FillArray(int[] buf, int size);

  [DllImport("dist/LibSalt.dylib")]
  public static extern uint nacl_randombytes_random();

  public static uint randombytes_random() {
    return nacl_randombytes_random();
  }

  [DllImport("dist/LibSalt.dylib")]
  public static extern void nacl_randombytes_buf(byte[] buf, int size); 

  public static void randombytes_buf(byte[] buf) {
    int size = buf.Length;
    nacl_randombytes_buf(buf, size);
  }

  [DllImport("dist/LibSalt.dylib")]
  public static extern void nacl_randombytes_buf_deterministic(byte[] buf, int size, byte[] seed);

  public static void randombytes_buf_deterministic(byte[] buf, byte[] seed) {
    int size = buf.Length;
    nacl_randombytes_buf_deterministic(buf, size, seed);
  }

  [DllImport("dist/LibSalt.dylib")]
  public static extern int nacl_crypto_sign_keypair(byte[] pk, byte[] sk);

  public static int crypto_sign_keypair(byte[] pk, byte[] sk) {
    return nacl_crypto_sign_keypair(pk, sk);
  }

  [DllImport("dist/LibSalt.dylib")]
  public static extern int nacl_crypto_sign_seed_keypair(byte[] pk, byte[] sk, byte[] seed);

  public static int crypto_sign_seed_keypair(byte[] pk, byte[] sk, byte[] seed) {
    return nacl_crypto_sign_seed_keypair(pk, sk, seed);
  }

  [DllImport("dist/LibSalt.dylib")]
  public static extern int nacl_crypto_sign(byte[] sm, byte[] m, ulong mlen, byte[] sk);

  public static int crypto_sign(byte[] sm, byte[] m, byte[] sk) {
    ulong mlen = (ulong) m.Length;
    return nacl_crypto_sign(sm, m, mlen, sk);
  }

  [DllImport("dist/LibSalt.dylib")]
  public static extern int nacl_crypto_sign_open(byte[] m, byte[] sm, ulong smlen, byte[] pk);

  public static int crypto_sign_open(byte[] m, byte[] sm, byte[] pk) {
    ulong smlen = (ulong) sm.Length;
    return nacl_crypto_sign_open(m, sm, smlen, pk);
  }
  
  [DllImport("dist/LibSalt.dylib")]
  public static extern int nacl_crypto_sign_BYTES();

  public static int crypto_sign_BYTES() {
    return nacl_crypto_sign_BYTES();
  }

  [DllImport("dist/LibSalt.dylib")]
  public static extern int nacl_randombytes_SEEDBYTES();

  public static int randombytes_SEEDBYTES() {
    return nacl_randombytes_SEEDBYTES();
  }
}
