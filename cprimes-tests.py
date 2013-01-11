import cprimes as cp
import itertools
import sys
import unittest

class Factor(unittest.TestCase):
	def test_factor(self):
		return
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

	def setUp(self):
		#http://primes.utm.edu/lists/small/
		self.big_primes = [
			#300 digit primes
			203956878356401977405765866929034577280193993314348263094772646453283062722701277632936616063144088173312372882677123879538709400158306567338328279154499698366071906766440037074217117805690872792848149112022286332144876183376326512083574821647933992961249917319836219304274280243803104015000563790123,
			531872289054204184185084734375133399408303613982130856645299464930952178606045848877129147820387996428175564228204785846141207532462936339834139412401975338705794646595487324365194792822189473092273993580587964571659678084484152603881094176995594813302284232006001752128168901293560051833646881436219,
			319705304701141539155720137200974664666792526059405792539680974929469783512821793995613718943171723765238853752439032835985158829038528214925658918372196742089464683960239919950882355844766055365179937610326127675178857306260955550407044463370239890187189750909036833976197804646589380690779463976173,
			]
	def test_small_nums(self):
		limit = 10 ** 4
		primes = cp.below(limit)
		rabin_results = [x for x in range(limit) if cp.is_prime(x)]
		self.assertEqual(primes, rabin_results)

	def test_big_primes(self):
		for p in self.big_primes:
			self.assertTrue(cp.is_prime(p))

	def test_big_nonprime(self):
		not_p = 743808006803554439230129854961492699151386107534013432918073439524138264842370630061369715394739134090922937332590384720397133335969549256322620979036686633213903952966175107096769180017646161851573147596390153
		
		self.assertFalse(cp.is_prime(not_p))

		#make and test some semiprimes
		for pair in itertools.product(self.big_primes, repeat = 2):
			a, b = pair
			self.assertFalse(cp.is_prime(a * b))

	def test_str_args(self):
		for p in map(str, self.big_primes):
			self.assertTrue(cp.is_prime(p))

		bad_strs = [ "123.4", "123-4", "", "d    1234    "]
		for bs in bad_strs:
			with self.assertRaises(ValueError):
				cp.is_prime(bs)

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
