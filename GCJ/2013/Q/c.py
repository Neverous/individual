import sys
import re
from math import sqrt

def palindrome(word):
    for x in xrange((len(word) + 1) / 2):
        if word[x] != word[-x - 1]:
            return False

    return True

pattern = re.compile('[0-9.]+')
result = set()
for ff in sys.argv[1:]:
    for number in pattern.findall(open(ff).read()):
        number = number.replace('.', '').strip()
        if number and palindrome(number):
            number = int(number)
            if number:
                num = int(sqrt(number))
                if num ** 2 == number and palindrome(str(num)):
                    result.add(number)

res = sorted(result)
for n in res:
    print(n)
