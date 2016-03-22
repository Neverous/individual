# -*- encoding: utf8 -*-
# 2012
# Maciej Szeptuch
# II UWr
import sys

for t in xrange(int(sys.stdin.readline())):
	typed, count = map(int, sys.stdin.readline().split())
	probabilities = map(float, sys.stdin.readline().split())
	best, act = count + 2.0, 1
	for p in xrange(typed):
		act *= probabilities[p]
		best = min(best, count + typed - 2 * p - 1 + (count + 1) * (1 - act))

	print 'Case #%d: %.10f' % (t + 1, best)

