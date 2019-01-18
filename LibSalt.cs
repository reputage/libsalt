using System.Collections;
using System.Collections.Generic;
using System;
using System.Runtime.InteropServices;

public class LibSalt {

  [DllImport("dist/simplemath.dylib")]
  public static extern double Add(double a, double b);

  [DllImport("dist/simplemath.dylib")]
  public static extern int RandInt();

  [DllImport("dist/simplemath.dylib")]
  public static extern void FillArray(int[] buf, int size);

  [DllImport("dist/LibSalt.dylib")]
  public static extern void nacl_randombytes(byte[] buf, int size);

  [DllImport("dist/LibSalt.dylib")]
  public static extern void nacl_randombytes_buf_deterministic(byte[] buf, int size, byte[] seed);

  public static string ByteArrayToString(byte[] ba) {
    return BitConverter.ToString(ba).Replace("-", "");
  } 
}