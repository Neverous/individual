import sys
data = sys.stdin.read().split('\n')
try:
	results = open('results', 'r').read().split('\n')

except:
	results = [0,0,0,0]

i = 0
for data in data[1:-1]:
	data = data.split()
	results[i] = int(results[i]) + int(data[-1])
	i += 1

file = open('results', 'w')
print >>file, results[0] 
print >>file, results[1] 
print >>file, results[2] 
print >>file, results[3] 

print '0: %d' % results[0]
print '1: %d' % results[1]
print '2: %d' % results[2]
print '3: %d' % results[3]
