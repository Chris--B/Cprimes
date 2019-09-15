Cprimes
=======

Project for finding and verifying primes. Core functionality is written in ANSI C, with Python bindings for ease of use. Makes use of the Miller-Rabin and Lucas-Lehmer algorithms, the Prime Number Theorem, and Sieve of Eratosthenes.

Usage
=====

The core functions are all written in Ansi C and can be called from C or C++. A Python module is provided that reexports the functions from the C DLL. Each function has its own header.

Building
========

This project should build out-of-the-box with CMake 3 and FetchContent (for Windows).

```
git clone git@github.com:Chris--B/Cprimes.git
cd Cprimes
mkdir _build && cd _build
cmake -G Ninja .. 
ninja
```

This will produce a `cprimes.dll` or `libcprimes.so` file in `_build/bin` along with some test artifacts.
GMP is expected to be installed on macOS or Linux systems so that CMake's `find_library()` can find it. On Windows, we host binaries on Github and include them using CMake.

Please open issues on Github if you encounter any problems.
