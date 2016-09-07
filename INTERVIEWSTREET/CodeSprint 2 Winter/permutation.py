import sys
import random

count = int(sys.stdin.readline())
permutation = [num for num in range(count)]
random.shuffle(permutation)
print(' '.join([str(n) for n in permutation]))
