//g++ LibSodiumTest.cpp -lsodium LibSodiumWrapper.cpp

#include "sodium.h"
#include "../LibSalt.h"
#include <iostream>

void Test() {
  if(sodium_init() < 0) {
     return;
  }

  std::cout << "\nLibSodium Test: RandomBytes" << std::endl;

  uint32_t n;
  n = randombytes_random();
  std::cout << "randombytes_random Value: " << n << std::endl;

  unsigned char out[16];
  static const unsigned char seed[randombytes_SEEDBYTES] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
    0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
    0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
  };

  randombytes_buf_deterministic(out, sizeof out, seed);
  std::cout << "randombytes_buf_deterministic Buffer:";
  for (int i = 0; i < sizeof out; ++i) {
      printf("%02x", out[i]);
  }
  std::cout << std::endl;
}

void Test2() {
  int size = 16;
  unsigned char buf[size];
  nacl_randombytes(buf, size);
  std::cout << "\nrandombytes BufferSize:" << size;
  std::cout << "\nrandombytes Buffer:";
  for (int i = 0; i < size; ++i) {
      printf("%02x", buf[i]);
  }
  std::cout << std::endl;
}

void Test3() {
  unsigned char seed[randombytes_SEEDBYTES] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
    0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
    0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
  };

  int size = 16;
  unsigned char buf[size];
  nacl_randombytes_buf_deterministic(buf, size, seed);
  std::cout << "\nrandombytes_buf_deterministic BufferSize:" << size;
  std::cout << "\nrandombytes_buf_deterministic Buffer:";
  for (int i = 0; i < size; ++i) {
      printf("%02x", buf[i]);
  }
  std::cout << std::endl;
}

void print(unsigned char buf[], int size) {
   for (int i = 0; i < size; ++i) {
      printf("%02x", buf[i]);
  }
  std::cout << std::endl; 
}

void Test4() {
  #define MESSAGE (const unsigned char *) "test"
  #define MESSAGE_LEN 4
  unsigned char pk[crypto_sign_PUBLICKEYBYTES];
  unsigned char sk[crypto_sign_SECRETKEYBYTES];
  crypto_sign_keypair(pk, sk);
  std::cout << "Sign Keypair: ";
  print(pk, crypto_sign_PUBLICKEYBYTES);
  print(sk, crypto_sign_SECRETKEYBYTES);

  unsigned char pk2[crypto_sign_PUBLICKEYBYTES];
  unsigned char sk2[crypto_sign_SECRETKEYBYTES];
  crypto_sign_keypair(pk2, sk2);
  std::cout << "Sign Keypair: ";
  print(pk2, crypto_sign_PUBLICKEYBYTES);
  print(sk2, crypto_sign_SECRETKEYBYTES);

  unsigned char signed_message[crypto_sign_BYTES + MESSAGE_LEN];
  unsigned long long signed_message_len;
  crypto_sign(signed_message, &signed_message_len,
              MESSAGE, MESSAGE_LEN, sk);
  unsigned char unsigned_message[MESSAGE_LEN];
  unsigned long long unsigned_message_len;
  int success = crypto_sign_open(unsigned_message, &unsigned_message_len,
                       signed_message, signed_message_len, pk);
  if(success == 0)
    std::cout << "Correct signature" << std::endl;
  else
    std::cout << "InCorrect signature" << std::endl;
  
  int success2 = crypto_sign_open(unsigned_message, &unsigned_message_len,
                       signed_message, signed_message_len, pk2);
  if(success2 == 0)
    std::cout << "Correct signature" << std::endl;
  else
    std::cout << "InCorrect signature" << std::endl;

}

void Test5() {
  #define MESSAGE (const unsigned char *) "test"
  #define MESSAGE_LEN 4
  unsigned char pk[crypto_sign_PUBLICKEYBYTES];
  unsigned char sk[crypto_sign_SECRETKEYBYTES];
  nacl_crypto_sign_keypair(pk, sk);
  std::cout << "Sign Keypair: ";
  print(pk, crypto_sign_PUBLICKEYBYTES);
  print(sk, crypto_sign_SECRETKEYBYTES);

  unsigned char pk2[crypto_sign_PUBLICKEYBYTES];
  unsigned char sk2[crypto_sign_SECRETKEYBYTES];
  nacl_crypto_sign_keypair(pk2, sk2);
  std::cout << "Sign Keypair: ";
  print(pk2, crypto_sign_PUBLICKEYBYTES);
  print(sk2, crypto_sign_SECRETKEYBYTES);

  unsigned char signed_message[crypto_sign_BYTES + MESSAGE_LEN];
  unsigned long long signed_message_len;
  nacl_crypto_sign(signed_message, MESSAGE, MESSAGE_LEN, sk);
  unsigned char unsigned_message[MESSAGE_LEN];
  unsigned long long unsigned_message_len;
  int success = nacl_crypto_sign_open(unsigned_message, signed_message, signed_message_len, pk);
  if(success == 0)
    std::cout << "Correct signature" << std::endl;
  else
    std::cout << "InCorrect signature" << std::endl;
  
  int success2 = nacl_crypto_sign_open(unsigned_message, signed_message, signed_message_len, pk2);
  if(success2 == 0)
    std::cout << "Correct signature" << std::endl;
  else
    std::cout << "InCorrect signature" << std::endl;
}

void Sizes() {
  std::cout << "PK Size:" << crypto_sign_PUBLICKEYBYTES << std::endl;;
  std::cout << "SK Size:" << crypto_sign_SECRETKEYBYTES << std::endl;
}

int main(void) {
  Test();
  Test2();
  Test3();
  Test4();
  Test5();
  Sizes();
  return 0;
}