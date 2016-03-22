/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)
#define GROUND -2
#define TREE -1

int monkeys,
	ttime,
	monkey[200020][2], // lewa, prawa
	connect[200020][2], // lewa, prawa
	timeline[400040][2], // kto, która ręka
	repr[200020][2]; // reprezentant, kiedy spadł
bool visited[200020]; // odwiedzony
std::vector<int> graph[200020];

void endOfTimesConnect(int vert, int flag);
int unionFind(int m);
int unionUnion(int a, int b, int t);

int main(void)
{
	for(int m = 0; m < 200020; ++ m)
	{
		repr[m][0] = m;
		repr[m][1] = GROUND;
	}

	scanf("%d %d\n", &monkeys, &ttime);
	for(int m = 0; m < monkeys; ++ m)
	{
		scanf("%d %d", &monkey[m][0], &monkey[m][1]);
		if(monkey[m][0] + 1)
			-- monkey[m][0];

		if(monkey[m][1] + 1)
			-- monkey[m][1];

		connect[m][0] = monkey[m][0];
		connect[m][1] = monkey[m][1];
	}


	for(int t = 0; t < ttime; ++ t)
	{
		scanf("%d %d", &timeline[t][0], &timeline[t][1]);
		-- timeline[t][0];
		-- timeline[t][1];
		connect[timeline[t][0]][timeline[t][1]] = -1;
	}

	for(int m = 0; m < monkeys; ++ m)
	{
		if(monkey[m][0] + 1)
		{
			graph[m].push_back(connect[m][0]);
			graph[connect[m][0]].push_back(m);
		}

		if(monkey[m][1] + 1)
		{
			graph[m].push_back(connect[m][1]);
			graph[connect[m][1]].push_back(m);
		}
	}

	endOfTimesConnect(0, TREE);
	for(int m = 0; m < monkeys; ++ m)
		if(!visited[m])
			endOfTimesConnect(m, GROUND);

	for(int t = ttime - 1; t >= 0; -- t)
		if(monkey[timeline[t][0]][timeline[t][1]] + 1)
			unionUnion(timeline[t][0], monkey[timeline[t][0]][timeline[t][1]], t);

	for(int m = 0; m < monkeys; ++ m)
	{
		unionFind(m);
		printf("%d\n", repr[m][1]);
	}

	return 0;
}

void endOfTimesConnect(int vert, int flag)
{
	visited[vert] = true;
	repr[vert][1] = flag;
	for(unsigned int s = 0; s < graph[vert].size(); ++ s)
		if(!visited[graph[vert][s]])
		{
			repr[graph[vert][s]][0] = vert;
			endOfTimesConnect(graph[vert][s], flag);
		}

	return;
}

int unionFind(int m)
{
	int father = repr[m][0];
	if(father == m)
		return m;

	repr[m][0] = unionFind(father);
	if(repr[m][1] == GROUND)
		repr[m][1] = repr[father][1];

	return repr[m][0];
}
int unionUnion(int a, int b, int t)
{
	int fA = unionFind(a),
		fB = unionFind(b);

	if(fA == fB)
		return false;

	if(repr[fA][1] == GROUND && repr[fB][1] != GROUND)
	{
		repr[fA][1] = t;
		repr[fA][0] = fB;
	}

	else if(repr[fA][1] != GROUND && repr[fB][1] == GROUND)
	{
		repr[fB][1] = t;
		repr[fB][0] = fA;
	}

	else if(fA < fB)
		repr[fB][0] = fA;

	else
		repr[fA][0] = fB;

	unionFind(a);
	unionFind(b);
	return true;
}
