
# LibSalt

LibSalt is simple C# wrapper library for Daniel J. Bernstein's nacl library via libsodium. This library only depends on C# and libsodium, and has no dependances on the .NET library. 

## Features

Libsodium is a simple library that only requires two files for installation for any C# project (on Mac).

## Basic Installation

The project depends on libsodium. (For Mac) This can be downloaded using Homebrew:

``` brew install libsodium ```

From the ```\dist``` folder you'll need ```LibSalt.dylib``` and ```LibSalt.cs```. Copy these files into your C# project.

## Build

To build the binaries locally use the make file:

``` make libsalt ```

This is will generate ```LibSalt.dylib``` in the ```\dist``` director. This along with LibSalt.cs is need to use the library.

## Tests

To build tests:

``` make build_tests ```

To run tests:

``` make run_tests ```

## Usage

LibSalt supports the following LibSodium functions:

- randombytes_random
- randombytes
- randombytes_buf_deterministic
- crypto_sign_bytes
- crypto_sign_keypair
- crypto_sign
- crypto_sign_open