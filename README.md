
# LibSalt

A simple C# wrapper for Daniel J. Bernstein's nacl library via libsodium.

## Features

Wrapper works for Mac for the following LibSodium functions:

- randombytes_random
- randombytes
- randombytes_buf_deterministic
- crypto_sign_bytes
- crypto_sign_keypair
- crypto_sign
- crypto_sign_open

## Installation

The project depends on libsodium. (For Mac) This can be downloaded using Homebrew:

``` brew install libsodium ```

To build the binaries locally use the make file:

``` make libsalt ```

This is will generate ```LibSalt.dylib```. This along with LibSalt.cs is need to use the library.

## Tests

To build tests:

``` make build_tests ```

To run tests:

``` make run_tests ```

## Usage

** TODO **
