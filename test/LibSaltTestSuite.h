// LibSaltTestSuite.h

#include "sodium.h"
#include "../LibSalt.h"
#include <string>
#include <iostream>
#include <typeinfo>
#include <cxxtest/TestSuite.h>

unsigned char seed[randombytes_SEEDBYTES] = {
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
  0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
  0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
};

unsigned char seed2[randombytes_SEEDBYTES] = {
  0x01, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
  0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
  0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
};

void print_in_hex_format(unsigned char input[], int size) {
  for (int i = 0; i < size; ++i) {
    printf("%02X", input[i]);
  }
}

void TS_ASSERT_DIFFERENT_DATA(unsigned char x[], unsigned char y[], int size) {
  bool isDifferent = false;
  for(int i = 0; i < size; i++)
    isDifferent = (x[i] == y[i]) ? isDifferent : true;
  TS_ASSERT(isDifferent);
}

class LibSaltTestSuite : public CxxTest::TestSuite
{
  
  public:
    void test_randombytes_buf(void) {
      std::cout << "\n Testing randombytes() .....";

      int size = 16;
      unsigned char buf[size];
      unsigned char buf2[size];
      nacl_randombytes(buf, size);
      nacl_randombytes(buf2, size);

      // Test for proper array size
      TS_ASSERT_EQUALS(sizeof buf, size);
      TS_ASSERT_EQUALS(sizeof buf2, size);

      // Test for generating different randombyte arrays 
      TS_ASSERT_DIFFERS(buf, buf2);
    } 

    void test_randombytes_random(void) {
      std::cout << "\n Testing randombytes_random() .....";

      // Test for proper variable size
      TS_ASSERT_EQUALS(sizeof randombytes_random(), sizeof randombytes_SEEDBYTES);
    }

    void test_randombytes_buf_deterministic(void) {
      std::cout << "\n Testing randombytes_buf_deterministic() .....";

      int size = 16;
      unsigned char buf[size];
      unsigned char buf2[size];
      unsigned char buf3[size];
      nacl_randombytes_buf_deterministic(buf, size, seed);
      nacl_randombytes_buf_deterministic(buf2, size, seed);
      nacl_randombytes_buf_deterministic(buf3, size, seed2);

      /*
      std::cout << std::endl;
      std::cout << "Buf1: ";
      print_in_hex_format(buf, 16);
      std::cout << std::endl;
      std::cout << "Buf2: ";
      print_in_hex_format(buf, 16);
      std::cout << std::endl;
      */

      TS_ASSERT_EQUALS(sizeof buf, size);
      TS_ASSERT_EQUALS(sizeof buf2, size); 
      TS_ASSERT_EQUALS(sizeof buf3, size); 

      // Test for generating same randombyte arrays with same seeds
      TS_ASSERT_SAME_DATA(buf, buf2, size); 

      // Test for generating different randombyte arrays with different seeds
      TS_ASSERT_DIFFERENT_DATA(buf, buf3, size);
      TS_ASSERT_DIFFERENT_DATA(buf2, buf3, size); 
    } 

    void test_crypto_sign_keypair(void) {
      std::cout << "\n Testing crypto_sign_keypair() .....";

      unsigned char pk[crypto_sign_PUBLICKEYBYTES];
      unsigned char sk[crypto_sign_SECRETKEYBYTES];
      unsigned char pk2[crypto_sign_PUBLICKEYBYTES];
      unsigned char sk2[crypto_sign_SECRETKEYBYTES];
      nacl_crypto_sign_keypair(pk, sk);
      nacl_crypto_sign_keypair(pk2, sk2);

      // Test for proper pk and sk array sizes
      TS_ASSERT_EQUALS(sizeof pk, crypto_sign_PUBLICKEYBYTES);
      TS_ASSERT_EQUALS(sizeof sk, crypto_sign_SECRETKEYBYTES);

      // Test for generating different random pk/sk  
      TS_ASSERT_DIFFERENT_DATA(pk, pk2, crypto_sign_PUBLICKEYBYTES);
      TS_ASSERT_DIFFERENT_DATA(sk, sk2, crypto_sign_SECRETKEYBYTES);
    }
    
    void test_crypto_sign_seed_keypair(void) {
      std::cout << "\n Testing crypto_sign_seed() .....";

      unsigned char pk[crypto_sign_PUBLICKEYBYTES];
      unsigned char sk[crypto_sign_SECRETKEYBYTES];
      unsigned char pk2[crypto_sign_PUBLICKEYBYTES];
      unsigned char sk2[crypto_sign_SECRETKEYBYTES];
      nacl_crypto_sign_seed_keypair(pk, sk, seed);
      nacl_crypto_sign_seed_keypair(pk2, sk2, seed);

      // Test for proper pk and sk array sizes
      TS_ASSERT_EQUALS(sizeof pk, crypto_sign_PUBLICKEYBYTES);
      TS_ASSERT_EQUALS(sizeof sk, crypto_sign_SECRETKEYBYTES);

      // Test for generating same pk/sk for same seed
      TS_ASSERT_SAME_DATA(pk, pk2, crypto_sign_PUBLICKEYBYTES);
      TS_ASSERT_SAME_DATA(sk, sk2, crypto_sign_SECRETKEYBYTES);
    }

    void test_crypto_sign(void) {
      std::cout << "\n Testing crypto_sign() .....";

      unsigned char * message = (unsigned char *) "test";
      int mlen = 4;
      unsigned char pk[crypto_sign_PUBLICKEYBYTES];
      unsigned char sk[crypto_sign_SECRETKEYBYTES];
      unsigned char pk2[crypto_sign_PUBLICKEYBYTES];
      unsigned char sk2[crypto_sign_SECRETKEYBYTES];

      crypto_sign_keypair(pk, sk);
      crypto_sign_keypair(pk2, sk2);

      unsigned char signed_message[crypto_sign_BYTES + mlen];
      unsigned long long smlen; 
      crypto_sign(signed_message, &smlen, message, mlen, sk);

      // Test for proper signed message length
      TS_ASSERT_EQUALS(smlen, crypto_sign_BYTES + mlen);
    }

    void test_crypto_sign_open(void) {
      std::cout << "\n Testing crypto_sign_open() .....";

      unsigned char * message = (unsigned char *) "test";
      int mlen = 4;

      unsigned char pk[crypto_sign_PUBLICKEYBYTES];
      unsigned char sk[crypto_sign_SECRETKEYBYTES];
      unsigned char pk2[crypto_sign_PUBLICKEYBYTES];
      unsigned char sk2[crypto_sign_SECRETKEYBYTES];
      crypto_sign_keypair(pk, sk);
      crypto_sign_keypair(pk2, sk2);

      unsigned char signed_message[crypto_sign_BYTES + mlen];
      unsigned long long smlen;
      crypto_sign(signed_message, &smlen, message, mlen, sk);

      unsigned char unsigned_message[mlen];
      unsigned long long unsigned_message_len;
      int success = crypto_sign_open(unsigned_message, &unsigned_message_len,
                       signed_message, smlen, pk);

      int success2 = crypto_sign_open(unsigned_message, &unsigned_message_len,
                       signed_message, smlen, pk2);

      // Test for sucessful decoding signed message with correct private key
      TS_ASSERT_EQUALS(success, 0);

      // Test for unsucessful decoding signed message with incorrect private key
      TS_ASSERT_DIFFERS(success2, 0);
    }

    void test_crypto_sign_bytes(void) {
      std::cout << "\n Testing crypto_sign_bytes() .....";

      int bytes = nacl_crypto_sign_BYTES();
      TS_ASSERT_EQUALS(bytes, crypto_sign_BYTES);
    }
};
