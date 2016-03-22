import sys
def check(data, balance = 0):
    if not data:
        return not balance

    for n in xrange(len(data)):
        if balance < 0:
            return False

        elif data[n].isalpha() or data[n] == ':':
            continue

        elif data[n] == '(':
            if n and data[n-1] == ':' and check(data[n+1:],  balance): # Eat smiley
                return True

            balance += 1

        elif data[n] == ')':
            if n and data[n-1] == ':' and check(data[n+1:],  balance): # Eat smiley
                return True

            balance -= 1

    return not balance

n = int(sys.stdin.readline())
for i in xrange(1, n+1):
    data = sys.stdin.readline().strip()
    print 'Case #%d: %s' % (i, "YES" if check(data) else "NO")
