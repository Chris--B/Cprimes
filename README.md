Cprimes
=======

Project for finding and verifying primes. Core functionality is written in ANSI C, with Python bindings for ease of use. Makes use of the Miller-Rabin and Lucas-Lehmer algorithms, the Prime Number Theorem, and Sieve of Eratosthenes.

Usage
=====

Bindings exists for only Python at the moment, but there are plans for other languages. The final binaries or scripts for these bindings can be found in the /bin directory of the CMake build tree. x64 builds *will not work* with x86 builds of Python. Make sure everything matches!

Everything can be called from straight C, although there isn't a unified, tidy header for that (yet).

TODO
====
In order of priority

1) General clean-up of the code.

2) Benchmarks.

3) Segmented Eratosthenes Sieve. It's really limiting not being able to divide up the sieving - 32-bit memory addressing shuts down sieving much past 1 billion. On 64-bit builds, sieving slows down to a crawl once swapping/paging starts. Compare performance with standard Eratosthenes Sieve.

4) Integrate tests and benchmarks into the build system, so they can be run when everything builds.

5) Build/export a 'primes.h'. It should be a single, self contained header file for interfacing the C-library. Using it instead of the collection in /cprimeslib/include would mean rebuilding everything every time the header changes, so it must be constructed from or include the other headers.

6) More bindings. In no particular order: C#, Lua, Java, Ruby, and Rust.

Building
========

You'll need 

* a C compiler
* [CMake](http://cmake.org) and your preferred build system. I'm found of [Ninja](http://martine.github.io/ninja/).
* [GMP](http://gmplib.org), [MPIR](http://mpir.org), or anything mimicking the interface.

Example:

	$ mkdir _build
	$ cd _build
	$ cmake -G "Ninja" .. -DCMAKE_BUILD_TYPE=Release
	$ ninja

Everything should build and run fine on Linux, OS X, and Windows, on both x86 and x64.
