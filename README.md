
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

`crypto_sign_keypair(byte[] pk, byte[] sk)` randomly generates a secret (`sk`) and public (`pk`) key 

### crypto_sign_seed_keypair

`crypto_sign_seed_keypair(byte[] pk, byte[] sk, byte[] seed)` randomly generates a secret (`sk`) and public (`pk`) key . Keys generated are based off the supplied `seed`, using the same seed will return the same keypair.

### crypto_sign

`crypto_sign(byte[] sm, byte[] m, byte[] sk)` prepends a signature to a message (`m`) using the secret key (`sk`). This generates a signed message in `sm`.

### crypto_sign_open

`crypto_sign_open(byte[] m, byte[] sm, byte[] pk)` checkes that the signed message (`sm`) has a valid signature for a given public key (`pk`). The valid public key will generate the unsigned message and store it in `m` and will return `0`. An invalid public key will return an non-zero value.

### crypto_sign_bytes

`crypto_sign_bytes` returns the size of signatures

