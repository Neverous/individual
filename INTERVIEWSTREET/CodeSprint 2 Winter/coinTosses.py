import sys
def e(n, m):
	if n == m:
		return 0

	if m == 0:
		return 2 ** (n + 1) - 2

	return 1 + e(n, m + 1) // 2 + e(n, 0) // 2

tests = int(sys.stdin.readline())
for t in range(tests):
	n, m = sys.stdin.readline().split()
	print('%d.00' % e(int(n), int(m)))
