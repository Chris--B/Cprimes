Cprimes
=======

Handling smallish prime numbers. (Under 18 decimal digits?)


Usage
=====

	[-c | --count X]        Counts primes less than or equal to X.
	[-r | --in-range Y X]      Sieves from Y to X and prints all primes in range.
	[-b | --below X]        Sieves from 0 to X and prints all primes in range.
	                         Same as -r 0 X
	[-o | --out FILE]       Change output from stdout to FILE
	[-h | --help]           Displays this information.

TODO
====
(In no particual order)

1) --in-range

2) Default option of checking for prime
	
	./primes 35

   should return false

3) Segmented Sieve

4) Multi-threading
*Definitely on basic eratos
*Maybe on segmented?

5) --count should be a modifier, not a stand alone option
