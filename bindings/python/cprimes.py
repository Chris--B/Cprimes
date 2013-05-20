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

_lucas_lehmer = cprimeslib.lucas_lehmer
_lucas_lehmer.restype = c_int
_lucas_lehmer.argtypes = [c_uint64]

def lucas_lehmer(power):
	"""Return True when 2^power - 1 is prime, and False otherwise. If power is not prime, raise a ValueError"""
	if not is_prime(power):
		raise ValueError("power must be prime.")
	return bool(_lucas_lehmer(power))


_eratos = cprimeslib.eratos
_eratos.restype = c_int
_eratos.argtypes = [c_uint64, POINTER(POINTER(c_uint64)), POINTER(c_size_t)]

def below(num):
	"""Return a list of all primes in the range [2, num). Raise a TypeError if num is not an int."""
	if not isinstance(num, int):
		#Errors like proper grammar too.
		text = num.__class__.__name__
		if(text[0].lower() in "aeiouh"):
			text = "an {}".format(text)
		else:
			text = "a {}".format(text)

		raise TypeError("num must be an int, not {}".format(text))
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
	"""
	Check whether or not num is prime.
		Raise a TypeError when num is not an int or string.
		Raise a ValueError when if num is a string which cannot be converted to an int by the built-in "int"
	"""
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

__all__ = ["is_prime", "below", "lucas_lehmer"]
