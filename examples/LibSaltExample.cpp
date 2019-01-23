//g++ LibSodiumTest.cpp -lsodium LibSodiumWrapper.cpp

#include "sodium.h"
#include "../LibSalt.h"
#include <iostream>

#define MESSAGE (const unsigned char *) "example"
#define MESSAGE_LEN 7

void example_init() {
  if(sodium_init() < 0) {
     return;
  }
}

void print_in_hex_format(unsigned char input[], int size) {
  for (int i = 0; i < size; ++i) {
    printf("%02X", input[i]);
  }
}

std::string to_string(unsigned char input[], int size) {
  std::string str(input, input + size / sizeof input[0] );
  return str;
} 

void example_randombytes_random() {
  std::cout << "\nExample: randombytes_random()" << std::endl;

  uint32_t n;
  n = randombytes_random();
  
  std::cout << "RandomValue: " << n << std::endl;
}

void example_randombytes_buf() {
  std::cout << "\nExample: randombytes_buf()" << std::endl;

  int size = 16;
  unsigned char buf[size];
  nacl_randombytes(buf, size);

  std::cout << "Buffer:";
  print_in_hex_format(buf, size);
  std::cout << std::endl;
}

void example_randombytes_buf_deterministic() {
  std::cout << "\nExample: randombytes_buf_deterministic()" << std::endl;

  unsigned char buf[16]; 
  static const unsigned char seed[randombytes_SEEDBYTES] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
    0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
    0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
  };

  randombytes_buf_deterministic(buf, sizeof buf, seed);
  std::cout << "Buffer: ";
  print_in_hex_format(buf, 16);
  std::cout << std::endl;
}

void example_randombytes_buf_deterministic2() {
  std::cout << "\nExample: randombytes_buf_deterministic2()" << std::endl;

  int size = 16;
  unsigned char buf[size];
  unsigned char seed[randombytes_SEEDBYTES] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
    0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
    0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
  };

  nacl_randombytes_buf_deterministic(buf, size, seed);
  std::cout << "Buffer:";
  print_in_hex_format(buf, size);
  std::cout << std::endl;
}

void example_crypto_sign_keypair() {
  std::cout << "\nExample: crypto_sign_keypair()" << std::endl;

  unsigned char pk[crypto_sign_PUBLICKEYBYTES];
  unsigned char sk[crypto_sign_SECRETKEYBYTES];
  unsigned char pk2[crypto_sign_PUBLICKEYBYTES];
  unsigned char sk2[crypto_sign_SECRETKEYBYTES];
  
  nacl_crypto_sign_keypair(pk, sk);
  nacl_crypto_sign_keypair(pk2, sk2);

  std::cout << "Keypair One: ";
  std::cout << "pk: ";
  print_in_hex_format(pk, crypto_sign_PUBLICKEYBYTES);
  std::cout << std::endl;
  std::cout << "sk: ";
  print_in_hex_format(sk, crypto_sign_SECRETKEYBYTES);
  std::cout << std::endl;

  std::cout << "Keypair Two: ";
  std::cout << "pk: ";
  print_in_hex_format(pk2, crypto_sign_PUBLICKEYBYTES);
  std::cout << std::endl;
  std::cout << "sk: ";
  print_in_hex_format(sk2, crypto_sign_SECRETKEYBYTES);
  std::cout << std::endl;
}

void example_crypto_sign_seed_keypair() {
  std::cout << "\nExample: crypto_sign_seed_keypair()" << std::endl;

  unsigned char seed[randombytes_SEEDBYTES] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
    0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
    0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
  };

  unsigned char pk[crypto_sign_PUBLICKEYBYTES];
  unsigned char sk[crypto_sign_SECRETKEYBYTES];
  unsigned char pk2[crypto_sign_PUBLICKEYBYTES];
  unsigned char sk2[crypto_sign_SECRETKEYBYTES];
  
  nacl_crypto_sign_seed_keypair(pk, sk, seed);
  nacl_crypto_sign_seed_keypair(pk2, sk2, seed);

  std::cout << "Keypair One: ";
  std::cout << "pk: ";
  print_in_hex_format(pk, crypto_sign_PUBLICKEYBYTES);
  std::cout << std::endl;
  std::cout << "sk: ";
  print_in_hex_format(sk, crypto_sign_SECRETKEYBYTES);
  std::cout << std::endl;

  std::cout << "Keypair Two: ";
  std::cout << "pk: ";
  print_in_hex_format(pk2, crypto_sign_PUBLICKEYBYTES);
  std::cout << std::endl;
  std::cout << "sk: ";
  print_in_hex_format(sk2, crypto_sign_SECRETKEYBYTES);
  std::cout << std::endl;
}

void example_crypto_sign() { 
  std::cout << "\nExample: example_crypto_sign()" << std::endl;
  
  unsigned char pk[crypto_sign_PUBLICKEYBYTES];
  unsigned char sk[crypto_sign_SECRETKEYBYTES];
  unsigned char pk2[crypto_sign_PUBLICKEYBYTES];
  unsigned char sk2[crypto_sign_SECRETKEYBYTES];
  nacl_crypto_sign_keypair(pk, sk);
  nacl_crypto_sign_keypair(pk2, sk2);

  unsigned char signed_message[crypto_sign_BYTES + MESSAGE_LEN];
  unsigned long long signed_message_len = crypto_sign_BYTES + MESSAGE_LEN;
  nacl_crypto_sign(signed_message, MESSAGE, MESSAGE_LEN, sk);

  std::cout << "Public Key: "; 
  print_in_hex_format(pk, crypto_sign_PUBLICKEYBYTES);
  std::cout << std::endl;

  std::cout << "Signed Message: "; 
  std::cout << to_string(signed_message, signed_message_len) << std::endl;

  unsigned char unsigned_message[MESSAGE_LEN];
  unsigned char unsigned_message2[MESSAGE_LEN];
  unsigned long long unsigned_message_len = MESSAGE_LEN;
  int success = nacl_crypto_sign_open(unsigned_message, signed_message, signed_message_len, pk);
  int success2 = nacl_crypto_sign_open(unsigned_message2, signed_message, signed_message_len, pk2);  
  
  std::cout << "Unsigned Message: "; 
  std::cout << to_string(unsigned_message, MESSAGE_LEN) << std::endl;

  std::cout << "Signature Verification for pk: "; 
  print_in_hex_format(pk, crypto_sign_PUBLICKEYBYTES);
  std::cout << std::endl;
  
  if(success == 0)
    std::cout << "Valid Signature" << std::endl;
  else
    std::cout << "Invalid signature" << std::endl;
  
  std::cout << "Signature Verification for pk2: "; 
  print_in_hex_format(pk2, crypto_sign_PUBLICKEYBYTES);
  std::cout << std::endl;

  if(success2 == 0)
    std::cout << "Valid signature" << std::endl;
  else
    std::cout << "Invalid signature" << std::endl;
}

void example_buffer_size_info() {
  std::cout << "\nBuffer Size Info" << std::endl;
  std::cout << "PK Size:" << crypto_sign_PUBLICKEYBYTES << std::endl;;
  std::cout << "SK Size:" << crypto_sign_SECRETKEYBYTES << std::endl;
}

int main(void) { 
  example_init();
  example_randombytes_random();
  example_randombytes_buf();  
  example_randombytes_buf();  
  example_randombytes_buf_deterministic();
  example_randombytes_buf_deterministic2();
  example_randombytes_buf_deterministic2();
  example_crypto_sign_keypair();
  example_crypto_sign_seed_keypair();
  example_crypto_sign(); 
  example_buffer_size_info();
  std::cout << std::endl;

  return 0;
}
