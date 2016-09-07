import sys

topics, questions, queries = sys.stdin.readline().split()
topics = int(topics)
questions = int(questions)
queries = int(queries)

topic = []
question = []
for t in range(topics):
	ID, lat, lon = sys.stdin.readline().split()
	topic.append((int(ID), float(lat), float(lon)))

for q in range(questions):
	line = sys.stdin.readline().split()
	if int(line[1]):
		question.append((int(line[0]), tuple([int(num) for num in line[2:]])))

top = [100000000000000000000 for t in range(1001)]
for q in range(queries):
	typ, count, lat, lon = sys.stdin.readline().split()
	count = int(count)
	lat = float(lat)
	lon = float(lon)
	for t, la, lo in topic:
		top[t] = (la - lat) ** 2 + (lo - lon) ** 2

	res = []
	if typ == 't':
		res = [str(-t) for _, t in sorted([(top[t], -t) for t, _, _ in topic])][:count]

	if typ == 'q':
		rep = [100000000000000000000 for q in range(1001)]
		for q, ts in question:
			for t in ts:
				rep[q] = min(rep[q], top[t])

		res = [str(-q) for _, q in sorted([(rep[q], -q) for q, _ in question])][:count]
	
	print(' '.join(res))
