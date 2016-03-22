import random
T = 10
print T
for t in xrange(T):
	H = 2
	O = 1000000
	print H, O
	for o in xrange(O):
		print o + random.randint(0, 1),

	print
