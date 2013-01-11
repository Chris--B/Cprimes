from ctypes import *
import math
import os
import string
import sys

#TODO: Unix friendly
try:
	cprimeslib = cdll.LoadLibrary("cprimes.dll")
except Exception as e:
	print("Error finding cprimes:\n\t{}".format(e))
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
		text = num.__class__.__name__
		if(text[0].lower() in "aeiouh"):
			text = "an {}".format(text)
		else:
			text = "a {}".format(text)

		raise TypeError("Num must be an int, not {}".format(text))
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
	if isinstance(num, int):
		num_arg = str(num).encode('utf-8')
	elif isinstance(num, str):
		try:
			int(num)
		except ValueError as e:
			raise e
		num_arg = num.encode('utf-8')
	else:
		text = num.__class__.__name__
		if(text[0].lower() in "aeiouh"):
			text = "an {}".format(text)
		else:
			text = "a {}".format(text)
		raise TypeError("Num must be an int or str, not {}".format(text))

	return bool(_miller_rabin(num_arg))

__all__ = ["is_prime", "below"]