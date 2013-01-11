from ctypes import *
import math
import os
import sys

try:
	cprimeslib = CDLL("cprimes.dll")
except Exception as e:
	print("Error finding libcprimes:\n\t{}".format(e))
	sys.exit(1)

_eratos = cprimeslib.eratos
_eratos.restype = c_int
_eratos.argtypes = [c_uint64, POINTER(POINTER(c_uint64)), POINTER(c_size_t)]

def below(num):
	"""
	Returns a list of all primes in the range [2, num). It is often faster to use is_prime when checking against a single instance of a number, rather than check for existance in this list. [Citation needed]

	>>> pyprimes.below(30)
	[2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
	"""
	if not isinstance(num, int):
		#Errors like proper grammar too.
		t = num.__class__.__name__
		if(t[0].lower() in "aeiouh"):
			t = "an {}".format(t)
		else:
			t = "a {}".format(t)

		raise TypeError("Num must be an int, not {}".format(t))
	elif num < 2:
		return []

	primes_arr = pointer(c_uint64())
	count = c_size_t()
	err = _eratos(num, byref(primes_arr), byref(count))
	if err:
		raise Exception(os.strerror(err))

	primes = primes_arr[:count.value]
	return primes

_miller_rabin = cprimeslib.miller_rabin
_miller_rabin.restype = c_int
_miller_rabin.argtypes = [c_char_p]

def is_prime(num):
	if not isinstance(num, int):
		raise TypeError("num must be an int")
	return bool(_miller_rabin(str(num).encode('utf-8')))

__all__ = ["is_prime", "below"]