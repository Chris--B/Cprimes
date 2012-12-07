from .c import below
from .primality import miller_rabin
import math

def factor(num):
	"""
	Return the prime factors of num.
	"""
	primes = below(int(math.sqrt(num)))
	small_factors = [x for x in primes if num % x == 0]
	#This is ugly as ass.
	big_factors = [num // x for x in small_factors if num % x == 0 and miller_rabin(num // x) and num // x not in small_factors]
	big_factors.reverse()
	return small_factors + big_factors