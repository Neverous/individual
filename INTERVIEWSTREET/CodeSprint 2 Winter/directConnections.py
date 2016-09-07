import sys
class iTree:
	_SIZE = 16384
	def __init__(self):
		self.clear()

	def clear(self):
		self.data = [[0, 0] for i in range(2 * self._SIZE)]
		return None

	def update(self, pos, value):
		p = self._SIZE + pos
		while p > 0:
			self.data[p][1] += value
			self.data[p][0] += 1
			p //= 2

		return None
	
	def getInterval(self, start, end, iStart = 0, iEnd = _SIZE - 1, pos = 1):
		if iStart == start and iEnd == end:
			return self.data[pos]

		iMiddle = (iStart + iEnd) // 2
		if end <= iMiddle:
			return self.getInterval(start, end, iStart, iMiddle, pos * 2)

		if start > iMiddle:
			return self.getInterval(start, end, iMiddle + 1, iEnd, pos * 2 + 1)

		a = self.getInterval(start, iMiddle, iStart, iMiddle, pos * 2)
		b = self.getInterval(iMiddle + 1, end, iMiddle + 1, iEnd, pos * 2 + 1)
		return (a[0] + b[0], a[1] + b[1])

tree = iTree()
tests = int(sys.stdin.readline())
for t in range(tests):
	cities = int(sys.stdin.readline())
	city = [c for c in range(cities)]
	position = [int(p) for p in sys.stdin.readline().split()]
	population = [int(p) for p in sys.stdin.readline().split()]
	city.sort(key = lambda x: position[x])
	result = 0
	tree.clear()
	for c in city:
		act = tree.getInterval(0, population[c])
		result += (position[c] * act[0] - act[1]) * population[c]
		tree.update(population[c], position[c])

	tree.clear()
	for c in reversed(city):
		act = tree.getInterval(0, population[c] - 1)
		result += (act[1] - position[c] * act[0]) * population[c]
		tree.update(population[c], position[c])

	print(result % 1000000007)
