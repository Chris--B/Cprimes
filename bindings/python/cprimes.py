from ctypes import *

import math
import os
import string
import sys

from ctypes.util import find_library

def addAnOrA(text):
	""" Add 'an' or 'a' to some text, depending on whether it starts with a vowel. """
	if(text[0].lower() in "aeiou"):
		return "an {}".format(text)
	return "a {}".format(text)

def load_cprimeslib():
	lib_path = find_library("cprimes") or find_library("libcprimes")

	# It's not where it should be. Maybe it's in the working directory?
	# Let's just try a bunch of names and hope for the best.
	if lib_path is None:
		names = [
			"./libcprimes.so", # Linux
			"./libcprimes.dylib", # OS X
			"./libcprimes.dll", "./cprimes.dll" # MinGW and MSVC windows, respectively
			]
		for name in names:
			# CDLL raises an exception when it cannot find the file
			# 	If it fails, move on to the next maybe name.
			# 	If not, we're done!
			try:
				lib = CDLL(name)
				break
			except:
				pass
	# Python found a file with the right name, but things could still go wrong.
	else:
		try:
			lib = CDLL(lib_path)
		except OSError as e:
			print("Error finding cprimes:\n\t{}".format(e))
			sys.exit(1)

	assert(lib is not None)
	return lib

cprimeslib = load_cprimeslib()

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
		raise TypeError("num must be an int, not {}".format(addAnOrA(num.__class__.__name__)))
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
		int(num)
		num_arg = num.encode('utf-8')
	else:
		raise TypeError("num must be an int or str, not {}".format(addAnOrA(num.__class__.__name__)))

	return bool(_miller_rabin(num_arg))

_low_estimate = cprimeslib.low_estimate
_low_estimate.restype = c_size_t
_low_estimate.argtypes = [c_uint64]

def low_estimate(num):
	if not isinstance(num, int):
		raise TypeError("num must be an integer, not {}".format(addAnOrA(num.__class__.__name__)))
	return _low_estimate(num)

_high_estimate = cprimeslib.high_estimate
_high_estimate.restype = c_size_t
_high_estimate.argtypes = [c_uint64]

def high_estimate(num):
	if not isinstance(num, int):
		raise TypeError("num must be an integer, not {}".format(addAnOrA(num.__class__.__name__)))
	return _high_estimate(num)

_good_estimate = cprimeslib.good_estimate
_good_estimate.restype = c_size_t
_good_estimate.argtypes = [c_uint64]

def good_estimate(num):
	if not isinstance(num, int):
		raise TypeError("num must be an integer, not {}".format(addAnOrA(num.__class__.__name__)))
	return _good_estimate(num)


__all__ = ["is_prime", "below", "lucas_lehmer", "low_estimate", "high_estimate", "good_estimate"]
