//randombytes_buf_deterministic
// g++ -dynamiclib -o libsodium_wrapper.dylib LibSodiumWrapper.cpp -lsodium

#include "sodium.h"
#include "LibSalt.h"

extern "C" unsigned int nacl_randombytes_random() {

    if(sodium_init() < 0) {
      return -1;
    }

    return randombytes_random();
}

extern "C" void nacl_randombytes_buf(unsigned char buf[], int size) {

  if(sodium_init() < 0) {
    return;
  }
  
  randombytes_buf(buf, size);
}

extern "C" void nacl_randombytes_buf_deterministic(unsigned char buf[], int size, unsigned char seed[]) {

  if(sodium_init() < 0) {
    return;
  }
  
  randombytes_buf_deterministic(buf, size, seed);
}

extern "C" int nacl_crypto_sign_keypair(unsigned char pk[], unsigned char sk[]) {
  if(sodium_init() < 0) {
    return -1;
  }

  return crypto_sign_keypair(pk, sk);
}

extern "C" int nacl_crypto_sign_seed_keypair(unsigned char pk[], unsigned char sk[], unsigned char seed[]) {
  if(sodium_init() < 0) {
    return -1;
  }

  return crypto_sign_seed_keypair(pk, sk, seed);
}

extern "C" int nacl_crypto_sign(unsigned char sm[], const unsigned char m[], unsigned long long mlen, const unsigned char sk[]) {

  if(sodium_init() < 0) {
    return -1;
  }

  unsigned long long smlen_p;
  return crypto_sign(sm, &smlen_p, m, mlen, sk);
}

extern "C" int nacl_crypto_sign_open(unsigned char m[], const unsigned char sm[], unsigned long long smlen, const unsigned char pk[]) {

  if(sodium_init() < 0) {
    return -1;
  }

  unsigned long long mlen_p;
  return crypto_sign_open(m, &mlen_p, sm, smlen, pk);
}

extern "C" int nacl_crypto_sign_BYTES() {
  
  if(sodium_init() < 0) {
    return -1;
  }

  return crypto_sign_bytes();
}

extern "C" int nacl_randombytes_SEEDBYTES() {
  if(sodium_init() < 0) {
    return -1;
  }

  return randombytes_seedbytes();
}

