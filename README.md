Cprimes
=======

Toy project of mine for finding prime numbers.

Usage
=====

Bindings exists for only Python at the moment, but there are plans for other languages. The final binaries or scripts for these bindings can be found in the /bin directory of the cmake build tree.

Everything can be called from straight C, although there isn't a unified, tidy header for that (yet).

TODO
====
In order of priority

1) General clean-up of the code. estimate{.c/.h} doesn't do anything and the code is in general, messy. It needs a thorough refactoring.

2) Segmented Eratosthenes Sieve. It's really limiting not being able to divide up the sieving - 32-bit memory addressing shuts down sieving much past 1 billion. On 64-bit builds, sieving slows down to a crawl once swapping/paging starts

3) Benchmarks. Along side the tests for correctness, there should be tests for speed to guage which options produce the best performance.

4) Build 'primes.h'. It should be a single, self contained header file for interfacing the C-library, but using it instead of the collection in /cprimeslib/include would mean rebuilding everything everytime the header changes. Not OK.

5) More bindings. C#, Lua, Java, and Ruby are all on the table.
