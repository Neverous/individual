import sys
def palindrome(word):
    for x in xrange((len(word) + 1) / 2):
        if word[x] != word[-x - 1]:
            return False

    return True

def _gen(length, word = '', zero = False):
    if not length:
        yield str(word)
        return

    for num in xrange(not zero, 4):
        for res in _gen(length - 1, word + str(num), True):
            yield res

result = set()
for l in xrange(int(sys.argv[1]), int(sys.argv[2])):
    for num in _gen(l):
        if num:
            num1 = int(num + ''.join(reversed(num))) ** 2
            if palindrome(str(num1)):
                result.add(num1)

        for c in xrange(4):
            num2 = int(num + str(c) + ''.join(reversed(num))) ** 2
            if palindrome(str(num2)):
                result.add(num2)

print sorted(result)
