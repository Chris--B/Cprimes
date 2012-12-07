from ctypes import CDLL, c_char_p, c_int, c_uint64, create_string_buffer, py_object

def make_buffer(thing):
	return create_string_buffer(bytes(str(thing), 'utf-8'))

cprimeslib = CDLL("pyprimes", use_errno = True)

#TODO: Seriously reconsider py_below. We need benchmarks.
_below = cprimeslib.py_below
_below.restype = py_object
_below.argtypes = [c_uint64]

def below(num):
	"""
	Returns a list of all primes <= num, an exact integer.

	>>>pyprimes.below(30)
	[2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
	"""
	if not isinstance(num, int):
		#Errors like in proper grammar too.
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
_millerrabin_round.restype = c_int
_millerrabin_round.argtypes = [c_char_p, c_char_p, c_uint64, c_uint64]

def millerrabin_round(num, d, s, witness):
	num_str = create_string_buffer(bytes(str(num), 'utf-8'))
	d_str = create_string_buffer(bytes(str(d), 'utf-8'))

	return bool(_millerrabin_round(num_str, d_str, s, witness))