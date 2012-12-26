import ctypes as _ctypes

cprimeslib = _ctypes.CDLL("cprimes", use_errno = True)

#TODO: Seriously reconsider py_below. We need benchmarks.
_below = cprimeslib.py_below
_below.restype = _ctypes.py_object
_below.argtypes = [_ctypes.c_uint64]

def below(num):
	"""
	Returns a list of all primes in the range [2, num]. It is often faster to use is_prime to check against a single instance of a number, rather than check for existance in this list. [Citation needed]

	>>>pyprimes.below(30)
	[2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
	"""
	if not isinstance(num, int):
		#Errors like proper grammar too.
		t = num.__class__.__name__
		if(t[0] in "aeiouAEIOU"):
			t = "an {}".format(t)
		else:
			t = "a {}".format(t)

		raise TypeError("Num must be an int, not {}".format(t))
	elif num < 0:
		raise ValueError("Num must be nonnegative.")
	return _below(num)

_millerrabin_round = cprimeslib.millerrabin_round
_millerrabin_round.restype = _ctypes.c_int
_millerrabin_round.argtypes = [_ctypes.c_char_p, _ctypes.c_char_p, _ctypes.c_uint64, _ctypes.c_uint64]

def millerrabin_round(num, d, s, witness):
	num_str = _ctypes.create_string_buffer(bytes(str(num), 'utf-8'))
	d_str = _ctypes.create_string_buffer(bytes(str(d), 'utf-8'))

	return bool(_millerrabin_round(num_str, d_str, s, witness))

def is_prime(num):
	#oeis a006945
	false_positives = [2047, 1373653, 25326001, 3215031751, 2152302898747, 3474749660383, 341550071728321, 3825123056546413051]
	if not isinstance(num, int):
		raise TypeError("num must be an int")
	if num < 20:
		return num in below(20)
	elif num % 2 == 0 or num in false_positives:
		return False
	d = num - 1
	s = 0
	while d % 2 == 0:
		d >>= 1
		s += 1
	return all((millerrabin_round(num, d, s, a) for a in below(20)))

__all__ = ["is_prime", "below"]