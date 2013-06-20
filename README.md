Cprimes
=======

Toy project of mine for finding prime numbers.

Usage
=====

Bindings exists for only Python at the moment, but there are plans for other languages. The final binaries or scripts for these bindings can be found in the /bin directory of the CMake build tree. x64 builds *will not work* with x86 builds of Python. Make sure everything matches.

Everything can be called from straight C, although there isn't a unified, tidy header for that (yet).

TODO
====
In order of priority

1) General clean-up of the code.

2) Segmented Eratosthenes Sieve. It's really limiting not being able to divide up the sieving - 32-bit memory addressing shuts down sieving much past 1 billion. On 64-bit builds, sieving slows down to a crawl once swapping/paging starts.

3) Benchmarks.

4) Integrate tests and benchmarks into the build system, so they can be run when everything builds.

5) Build/export a 'primes.h'. It should be a single, self contained header file for interfacing the C-library, but using it instead of the collection in /cprimeslib/include would mean rebuilding everything every time the header changes. Not OK.

6) More bindings. C#, Lua, Java, and Ruby to name a few.

Building
========

You'll need 

* a C compiler
* [CMake](http://cmake.org) and your preferred build system. I use [Ninja](http://martine.github.io/ninja/).
* [GMP](http://gmplib.org), [MPIR](http://mpir.org), or anything mimicking the interface.

Example:

	$ mkdir _build
	$ cd _build
	$ cmake -G "Ninja" .. -DCMAKE_BUILD_TYPE=Release
	$ ninja

Everything should build and run fine on Linux, OS X, and Windows, both x86 and x64.
