/* 2011
 * Maciej Szeptuch
 * -*-*-*-*-*-*-*-*-
 */
#include<cstdio>
#include<algorithm>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

const int BUFFER = 4096;
int p = BUFFER - 1;
char buffer[BUFFER];

int getInt(void)
{
	int number = 0;
	while((buffer[p] < '0' || buffer[p] > '9') && ++ p)
		if(p == BUFFER)
		{
			fread(buffer, sizeof(char), BUFFER, stdin);
			p = 0;
		}

	while(buffer[p] >= '0' && buffer[p] <= '9')
	{
		number = number * 10 + buffer[p] - '0';
		++ p;

		if(p == BUFFER)
		{
			fread(buffer, sizeof(char), BUFFER, stdin);
			p = 0;
		}
	}

	return number;
}

char getLetter(void)
{
	char letter = 0;
	while((buffer[p] < 'A' || buffer[p] > 'Z') && ++ p)
		if(p == BUFFER)
		{
			fread(buffer, sizeof(char), BUFFER, stdin);
			p = 0;
		}

	if(buffer[p] >= 'A' && buffer[p] <= 'Z')
	{
		letter = buffer[p];
		++ p;

		if(p == BUFFER)
		{
			fread(buffer, sizeof(char), BUFFER, stdin);
			p = 0;
		}
	}

	return letter;
}
 
int tests,
	size,
	moves,
	move,
	questions,
	qMoves[16],
	qNumber[16],
	question[16],
	answer[16],
	powers[32] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824};
long long int templ[32][2048],
			  temp[2048],
			  safe[2048];
char side[4];
const int PRIME = 1000033;
 
inline static const int $(const int &a){return (size + a) % size;}
inline static const bool moveCompare(const int &a, const int &b){return qMoves[a] < qMoves[b];}
int doMoves(const int &count);
void generateTemplate(const int &max);
 
int main(void)
{
	tests = getInt();
	for(int t = 0; t < tests; ++ t)
	{
		size = getInt(); moves = getInt();
		for(int s = 0; s < size; ++ s)
		{
			for(int p = 0; p < 32; ++ p)
				templ[p][s] = 0;
 
			safe[s] = 0;
		}
 
		safe[0] = 1;
		for(int m = 0; m < moves; ++ m)
		{
			side[0] = getLetter(); move = getInt();
			++ templ[0][side[0] == 'L'?$(move):$(-move)];
		}
 
		questions = getInt();
		for(int q = 0; q < questions; ++ q)
		{
			qMoves[q] = getInt(); qNumber[q] = getInt();
			-- qNumber[q];
			question[q] = q;
		}
 
		std::sort(question, question + questions, moveCompare);
		generateTemplate(qMoves[question[questions - 1]]);
		move = 0;
		for(int q = 0, count = 0; q < questions; ++ q)
		{
			count = qMoves[question[q]] - move;
			while(count)
				count = doMoves(count);
 
			move = qMoves[question[q]];
			answer[question[q]] = safe[qNumber[question[q]]];
		}
 
		for(int q = 0; q < questions; ++ q)
			printf("%d\n", answer[q]);
	}
 
	return 0;
}
 
void generateTemplate(const int &max)
{
	for(int p = 1; powers[p] <= max; ++ p)
	{
		for(int s = 0; s < size; ++ s)
			if(templ[p - 1][s]) for(int t = 0; t < size; ++ t)
				if(templ[p - 1][t])
					templ[p][$(s + t)] = templ[p - 1][s] * templ[p - 1][t] + templ[p][$(s + t)];

		for(int s = 0; s < size; ++ s)
			templ[p][s] %= PRIME;
	}

 
	return;
}
 
int doMoves(const int &count)
{
	if(!count)
		return 0;
 
	int p = std::upper_bound(powers, powers + 30, count) - powers - 1;
	for(int s = 0; s < size; ++ s)
		temp[s] = 0;
 
	for(int s = 0; s < size; ++ s)
		if(safe[s]) for(int t = 0; t < size; ++ t)
			if(templ[p][t])
				temp[$(s + t)] = safe[s] * templ[p][t] + temp[$(s + t)];
 
	for(int s = 0; s < size; ++ s)
		safe[s] = temp[s] % PRIME;
 
	return count - powers[p];
}
