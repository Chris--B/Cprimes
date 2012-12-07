from .c import below, millerrabin_round

#oeis a006945
miller_rabin_false_pos = [2047, 1373653, 25326001, 3215031751, 2152302898747, 3474749660383, 341550071728321, 3825123056546413051]

def miller_rabin(num, tests = 20):
	if num < 20: #I don't know why I need this....
		return num in below(20)
	elif num % 2 == 0 or num in miller_rabin_false_pos:
		return False
	d = num - 1
	s = 0
	while d % 2 == 0:
		d >>= 1
		s += 1
	return all((millerrabin_round(num, d, s, a) for a in below(20)))

