# 2012
# Maciej Szeptuch
# II UWr
import sys

def test(i, a, players, player, _sum):
	pot = a
	score = player[i] + a * _sum
	for j in xrange(players):
		if i != j:
			pot += max(0.0, (score - player[j]) / _sum)
			if pot > 1.0:
				return False

	return True

for t in xrange(int(sys.stdin.readline())):
	print 'Case #%d:' % (t + 1),
	data = map(float, sys.stdin.readline().split())
	players = int(data[0])
	player = data[1:]
	_sum = sum(player)
	for p in xrange(players):
		l, r = 0.0, 1.0
		for _ in xrange(50):
			mid = (l + r) / 2.0
			if test(p, mid, players, player, _sum):
				l = mid

			else:
				r = mid

		print '%.6f' % (l * 100), 
	
	print ''
