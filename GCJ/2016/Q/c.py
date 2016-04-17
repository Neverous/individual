import multiprocessing
from sympy.ntheory import factorint, isprime

JAMCOINS = 500
THREADS = 12
SIZE = 32

queue = multiprocessing.Queue(JAMCOINS)

def genRanges(start, end, count):
    step = (end - start) // count
    ranges = []
    for i in range(start + 1, end - step + 1, step):
        ranges.append((i, i + step))

    ranges[-1] = (ranges[-1][0], end)
    return ranges

def isItJamCoin(number):
    binnumber = bin(number)[2:]
    divisors = []
    for i in range(2, 11):
        current = int(binnumber, i)
        if isprime(current):
            return None

        divisor = min(factorint(current).keys())
        if divisor == current:
            return None

        divisors.append(divisor)

    return divisors

def findJamCoins(_range):
    try:
        start, end = _range
        for number in range(start, end, 2):
            divisors = isItJamCoin(number)
            if divisors:
                queue.put((number, divisors), False)

    except:
        pass

if __name__ == "__main__":
    pool = multiprocessing.Pool(THREADS)
    pool.map(findJamCoins, genRanges(2**(SIZE-1), 2**SIZE, THREADS))

    print("Case #1:")
    while not queue.empty():
        jamcoin, divisors = queue.get()
        print("%032d" % (int(bin(jamcoin)[2:])), " ".join(map(str, divisors)))
