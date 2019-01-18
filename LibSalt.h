
extern "C" int nacl_randombytes_random();

extern "C" void nacl_randombytes(unsigned char * buf, int size);

extern "C" void nacl_randombytes_buf_deterministic(unsigned char * buf, int size, unsigned char * seed);

extern "C" int nacl_crypto_sign_BYTES();

extern "C" int nacl_crypto_sign_keypair(unsigned char *pk, unsigned char *sk);

extern "C" int nacl_crypto_sign(unsigned char *sm, const unsigned char *m, unsigned long long mlen, const unsigned char *sk);

extern "C" int nacl_crypto_sign_open(unsigned char *m, const unsigned char *sm, unsigned long long smlen, const unsigned char *pk);
