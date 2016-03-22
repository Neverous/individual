import sys
from collections import defaultdict
n = int(sys.stdin.readline())
for i in xrange(1, n + 1):
    count = defaultdict(lambda: 0)
    sentence = sys.stdin.readline().strip().lower()
    for letter in sentence:
        if letter.isalpha():
            count[letter] += 1

    result = 0
    for w, cnt in zip(xrange(26, 0, -1), reversed(sorted(count.values()))):
        result += w * cnt

    print 'Case #%d: %d' % (i, result)
