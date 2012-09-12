#ifndef _PRIMES_H_
#define _PRIMES_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <inttypes.h>
#include <stddef.h>

/*
	Return number of primes found,
	store found primes in *PRIMES_ARRAY
	
	Sieve of Eratosthenes, as described on Programming Praxis.
		http://programmingpraxis.com/2009/02/19/sieve-of-eratosthenes/
	
	TODO: Segmented Sieve of Eratosthenes 
		http://programmingpraxis.com/2010/02/05/segmented-sieve-of-eratosthenes/
*/
size_t eratos(int n, uint64_t** primes_array);

#ifdef __cplusplus
}
#endif

#endif // _PRIMES_H_