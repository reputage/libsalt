
# LibSodium C#

A simple C# wrapper for libsodium

## Features

Wrapper works for Mac for the following LibSodium functions:

-randombytes_random
-randombytes
-randombytes_buf_deterministic
-crypto_sign_bytes
-crypto_sign_keypair
-crypto_sign
-crypto_sign_open

## Installation

Install libsodium using Homebrew:

``` brew install libsodium ```

## Builds

The following are simple commands to build the wrapper:

Building Wrapper
g++ -dynamiclib -o libsodium_wrapper.dylib LibSodiumWrapper.cpp -lsodium

Building Test
g++ LibSodiumTest.cpp -lsodium LibSodiumWrapper.cpp
