import cprimes as cp
import unittest
import sys

class Factor(unittest.TestCase):
	def test_factor(self):
		raise NotImplementedError()
		#Two 8-digit prime factors of Googolplex + 10
		#http://www.alpertron.com.ar/googol.pl?digits=8
		a, b = 10838917, 11072557
		self.assertEqual(cp.factor(a * b), [a, b])

		self.assertEqual(cp.factor(31 * 29), [29, 31])

		self.assertEqual(cp.factor(2 ** 2), [2])
		self.assertEqual(cp.factor(2 ** 27), [2])

		self.assertEqual(cp.factor(2 * 3 * 4 * 5), [2, 3, 5])

		self.assertEqual(cp.factor(math.factorial(37)), cp.below(38))

class MillerRabin(unittest.TestCase):
	def test_small_nums(self):
		limit = 10 ** 4
		primes = cp.below(limit)
		rabin_results = [x for x in range(limit) if cp.is_prime(x)]
		self.assertEqual(primes, rabin_results)

	def test_big_prime(self):
		big_p = 643808006803554439230129854961492699151386107534013432918073439524138264842370630061369715394739134090922937332590384720397133335969549256322620979036686633213903952966175107096769180017646161851573147596390153
		self.assertTrue(cp.is_prime(big_p))

	def test_big_nonprime(self):
		not_p = 743808006803554439230129854961492699151386107534013432918073439524138264842370630061369715394739134090922937332590384720397133335969549256322620979036686633213903952966175107096769180017646161851573147596390153
		self.assertFalse(cp.is_prime(not_p))

	def test_raises_TypeError(self):
		with self.assertRaises(TypeError):
			cp.is_prime(557.0)

class Below(unittest.TestCase):
	def test_0_is_empty(self):
		self.assertEqual(cp.below(0), [])
	
	def test_30_is_correct(self):
		self.assertEqual(cp.below(30), [2, 3, 5, 7, 11, 13, 17, 19, 23, 29])
	
	def test_15mil_is_1mil_long(self):
		self.assertEqual(len(cp.below(15485864)), 1000000)
		
	def test_raises_TypeErrors(self):
		with self.assertRaises(TypeError):
			cp.below(30.0)

if __name__ == "__main__":
	unittest.main(verbosity = 2)
