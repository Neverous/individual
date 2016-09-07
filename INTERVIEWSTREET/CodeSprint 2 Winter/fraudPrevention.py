import sys
import collections

state = {
	'il': 'il',
	'illinois': 'il',
	'ny': 'ny',
	'new york': 'ny',
	'ca': 'ca',
	'california': 'ca',
	}

def cleanupEmail(mail):
	user, server = mail.split('@')
	username = ''
	copy = True
	for l in user:
		if l == '.':
			continue

		if l == '+':
			break

		username += l

	return username + '@' + server

def cleanupStreet(street):
	return street.replace(' street', ' st.').replace(' road', ' rd.')

countFraudlentByMail = collections.defaultdict(lambda: collections.defaultdict(set))
countFraudlentByAddress = collections.defaultdict(lambda: collections.defaultdict(set))

sys.stdin.readline()
lines = sys.stdin.read().lower().strip().split('\n')
# PREPROCESS LINES
for l, line in enumerate(lines):
	line = line.strip().split(',')
	lines[l] = (
		int(line[0].strip()), # Order ID
		int(line[1].strip()), # Deal ID
		cleanupEmail(line[2].strip()), # Email
		cleanupStreet(line[3].strip()), # Street Address
		line[4].strip(), # City
		state[line[5].strip()], # State
		line[6].strip(), # ZIP Code
		int(line[7].strip()), # Credit card
		)

	countFraudlentByMail[lines[l][1]][lines[l][2]].add(lines[l][7])
	countFraudlentByAddress[lines[l][1]]['%s:%s:%s:%s'%lines[l][3:7]].add(lines[l][7])

res = []
for ID, deal, email, street, city, state, zipcode, credit in lines:
	for count in (
		len(countFraudlentByMail[deal][email]),
		len(countFraudlentByAddress[deal]['%s:%s:%s:%s'%(street, city, state, zipcode)]),
		):
		if count > 1:
			res.append(str(ID))
			break;

print(','.join(res))
