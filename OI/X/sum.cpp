/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<queue>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)
#define INFTY (1 << 30)

int coins,
	modulo,
	coin,
	questions,
	question,
	edges,
	edge[8192],
	rest[65536],
	act;
bool processed[65536];

std::priority_queue<std::pair<int, int> > que;

inline static int MIN(int a, int b);
inline static void preprocess(void);

int main(void)
{
	scanf("%d %d", &coins, &modulo);
	for(int r = 0; r < modulo; ++ r)
	{
		rest[r] = INFTY;
		edge[r] = INFTY;
	}

	for(int c = 0; c < coins - 1; ++ c)
	{
		scanf("%d", &coin);
		edge[coin % modulo] = MIN(edge[coin % modulo], coin);
	}

	for(int r = 0; r < modulo; ++ r)
		if(edge[r] != INFTY)
			edge[edges ++] = edge[r];

	preprocess();
	scanf("%d", &questions);
	for(int q = 0; q < questions; ++ q)
	{
		scanf("%d", &question);
		printf("%s\n", rest[question % modulo] <= question?"TAK":"NIE");
	}

	return 0;
}

inline static int MIN(int a, int b)
{
	return a<b?a:b;
}

inline static void preprocess(void)
{
	que.push(std::make_pair(0, 0));
	rest[0] = 0;
	while(!que.empty())
	{
		act = que.top().second;
		que.pop();

		if(processed[act])
			continue; // Solution already found

		processed[act] = true;
		for(int e = 0; e < edges; ++ e)
			if(rest[(act + edge[e]) % modulo] > rest[act] + edge[e])
			{
				rest[(act + edge[e]) % modulo] = rest[act] + edge[e];
				que.push(std::make_pair(-rest[(act + edge[e]) % modulo], (act + edge[e]) % modulo));
			}
	}

	return;
}

