
# LibSalt

LibSalt is simple C# wrapper library for Daniel J. Bernstein's nacl library via libsodium. This library only depends on C# and libsodium, and has no other dependances. 

## Features

Libsalt is a simple library. You can integrate libsalt into any C# project using either ```LibSalt.dylib``` with ```LibSalt.cs``` or with the ```LibSalt.dll```. These files are given with each release or can be built locally on Mac.

## Basic Installation

The project depends on libsodium. (For Mac) This can be downloaded using Homebrew:

``` brew install libsodium ```

From the ```\dist``` folder you'll need ```LibSalt.dylib``` and ```LibSalt.cs```. Copy these files into your C# project.

## Build

To build the binaries locally use the make file:

``` make build ```

This is will generate ```LibSalt.dylib``` in the ```\dist``` director. This along with LibSalt.cs is need to use the library.

## Tests

To build and run tests for bindings:

``` make tests ``` 

## API Usage

LibSalt supports functions for:

- Generating random data
  - [randombytes_random](#randombytes_random)
  - [randombytes](#randombytes)
  - [randombytes_buf_deterministic](#randombytes_buf_deterministic)
- Public key pair generation
  - [crypto_sign_keypair](#crypto_sign_keypair)
  - [crypto_sign_seed_keypair](#crypto_sign_seed_keypair)
- Public-key signature generation
  - [crypto_sign](#crypto_sign)
  - [crypto_sign_open](#crypto_sign_open)
  - [crypto_sign_bytes](#crypto_sign_bytes)

## API Docs

### randombytes_random

`randombytes_random()` returns a random 32 bit (4-btye) integer i.e. a number between `0` and `0xffffffff`

### randombytes

`randombytes(byte[] buf)` fills a byte array with a random sequence of bytes into `buf`

### randombytes_buf_deterministic

`randombytes_buf_deterministic(byte[] buf, byte[] seed)` fills a byte array (`buf`) with a random sequence of bytes. This random sequence of bytes is based on the input `seed`. Use the same seed to get the same random sequence of bytes for `buf`. 

### crypto_sign_keypair

`crypto_sign_keypair(byte[] pk, byte[] sk)` randomly generates a secret and private key i.e. `sk` and `pk` respectively

### crypto_sign_seed_keypair

`crypto_sign_seed_keypair(byte[] pk, byte[] sk, byte[] seed)` randomly generates a secret and private key i.e. `sk` and `pk` respectively. Key generated are based off the supplied `seed`, using the same seed will return the same keypair.

### crypto_sign

`crypto_sign(byte[] sm, byte[] m, ulong mlen, byte[] sk)` prepends a signature to a message using the secret key. `sm` is the reference to the signed message, `m` is the message, `mlen` is the length of the message, and `sk` is the secret key used to sign the message.

### crypto_sign_open

`crypto_sign_open(byte[] m, byte[] sm, ulong smlen, byte[] pk)` checkes that the signed message has a valid signature for a given public key. `m` is the reference to the unsigned message, `sm` is a reference to the signed message, `smlen` is the length of the signed message and `pk` is the public key used to check the signature. 

### crypto_sign_bytes

`crypto_sign_bytes` returns the size of signatures

