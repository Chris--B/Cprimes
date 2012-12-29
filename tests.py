import cprimes
import unittest

class Testcprimes(unittest.TestCase):
	def test_below(self):
		self.assertEqual(cprimes.below(0), [])
		self.assertEqual(cprimes.below(30), [2, 3, 5, 7, 11, 13, 17, 19, 23, 29])
		self.assertEqual(len(cprimes.below(15485864)), 1000000)
		with self.assertRaises(TypeError):
			cprimes.below(30.0)

	def test_factor(self):
		print("Factor not implemented.")
		return
		#Two 8-digit prime factors of Googolplex + 10
		#http://www.alpertron.com.ar/googol.pl?digits=8
		a, b = 10838917, 11072557
		self.assertEqual(cprimes.factoring.factor(a * b), [a, b])

		self.assertEqual(cprimes.factoring.factor(31 * 29), [29, 31])

		self.assertEqual(cprimes.factoring.factor(2 ** 2), [2])
		self.assertEqual(cprimes.factoring.factor(2 ** 5), [2])
		self.assertEqual(cprimes.factoring.factor(2 ** 27), [2])

		self.assertEqual(cprimes.factoring.factor(2 * 3 * 4 * 5), [2, 3, 5])

	def test_miller_rabin(self):
		primes = cprimes.below(50)
		rabin_results = [x for x in range(primes[-1] + 1) if cprimes.is_prime(x)]
		self.assertEqual(primes, rabin_results)

		big_p = 643808006803554439230129854961492699151386107534013432918073439524138264842370630061369715394739134090922937332590384720397133335969549256322620979036686633213903952966175107096769180017646161851573147596390153
		self.assertTrue(cprimes.is_prime(big_p))

		not_p = 743808006803554439230129854961492699151386107534013432918073439524138264842370630061369715394739134090922937332590384720397133335969549256322620979036686633213903952966175107096769180017646161851573147596390153
		self.assertFalse(cprimes.is_prime(not_p))

		with self.assertRaises(TypeError):
			cprimes.is_prime(557.0)

if __name__ == "__main__":
	pass
