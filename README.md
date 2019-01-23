
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

## Usage

LibSalt supports functions for:

- Generating random data
- Public key pair generation
- Public-key signature generation

These are the currenlty supprted libsodium functions:

- randombytes_random
- randombytes
- randombytes_buf_deterministic
- crypto_sign_bytes
- crypto_sign_keypair
- crypto_sign
- crypto_sign_open

### randombytes

`randombytes(byte[] buf)` fills a byte array with a random sequence of bytes

### randombytes_buf_deterministic

`randombytes_buf_deterministic(byte[] buf, byte[] seed)` fills a byte array with a random sequence of bytes. This random sequence of bytes is based on a seed. Use the same seed across function calls to get the same random sequence of bytes. 

### randombytes_random

`randombytes_random()` returns a random 32 bit (4-btye) integer i.e. a number between `0` and `0xffffffff`


### crypto_sign_keypair

`crypto_sign_keypair()` randomly generates a secret and private key

### crypto_sign

`crypto_sign()` prepends a signature to a message using the secret key

### crypto_sign_open

`crypto_sign_open()` checkes that the signed message has a valid signature for a given public key

### crypto_sign_bytes

`crypto_sign_bytes` returns the size of signatures

