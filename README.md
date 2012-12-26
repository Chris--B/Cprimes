Cprimes
=======

Library for all things prime-number related. Finding them, checking them, factoring numbers with them, the works.

Usage
=====

All of the C-functions are declared in "primes.h", and linkable from the DLL. (I know DLLs are Windows-specific, I'm working on it.)

Right now, it depends on a dynamically linked gmp DLL. I've been using libgmp-3.dll, because building it on Windows isn't pleasant. The exact name is defined in the root-level makefile. Not sure whether to use static or dynamic linking because of licensing issues - I'm aiming for MIT, but GMP is under LGPL. I don't yet understand licenses. 

TODO
====
(In no particular order)

1) Better build system. I don't like gmake. Whether this is a lack of knowledge on my part, or antiqued design on theirs I'm not sure. Probably the first. Either way, I'm impatient and don't want to deal with it. Thinking of writing a Python script to build everything for me.

2) Segmented Eratosthenes Sieve. It's really limiting not being able to divide up the sieving - I can barely get past 10^9 for checking primes before my laptop runs out of contiguous RAM.

3) Benchmarks. I wrote part of the Python wrappers in C because I though it'd be more efficient, but I don't have all that much evidence for the case. Setting up some tests were amazing in making sure everything works. Benchmarks are a must.

4) Test the C code. I have what I feel is fairly comprehensive testing on the Python wrappings, and to an extent that ensures the C code works properly, but I'd like to be sure.

5) Ruby, C#, and Java bindings. In that order, unless I get caught up in some new hype.