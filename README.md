# Permissions Serializer

## Author
 - George Kobrusev, gr. 12b, course 3, FAMCS 2025

## Overview
 - A simple tool for serialization of file and its owner basic permissions for transfer
 - It's supposed to be deployable on different platforms like *Windows, Linux or MacOS* or theoretically anything unix-like
 
## Usage
 - This tool gets basic permissions (*read, write, execute*) for file owner, serializes them with a file and encrypts them. <br> Deserialization proceeds vice versa
 - Data integrity is protected via additional block of data which is checked after decryption

## Building
 - This project uses <code>CMake</code> for building. See <code>CMakeLists.txt</code> for build specifications.
 - Change <code>USE_FLTK</code> option to build a CLI or GUI version
 - Building requires <code>C++17</code> or higher language standard support

## Additional notes
 - This project contains dependencies written by other deverlopers:
    * [TinyAES](https://github.com/kokke/tiny-AES-c) for encryption
    * [FLTK v1.5.0](https://github.com/fltk/fltk) for GUI
