/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int verts,
	start,
	end,
	ants,
	ladybug,
	landplace,
	antToVert[1010],
	vertToAnt[5050],
	direction[5050],
	score[1010];
bool moved[1010],
	 state[5050];

std::vector<int> tree[5050];
std::queue<int> que;

inline static void simulate(int landing);
inline static void directTree(int root);
inline static void moveAnts(void);
inline static void floodAgainst(void);
inline static void floodAgainst(int root);

int main(void)
{
	scanf("%d", &verts);
	for(int e = 1; e < verts; ++ e)
	{
		scanf("%d %d", &start, &end);
		-- start;
		-- end;
		tree[start].push_back(end);
		tree[end].push_back(start);
		vertToAnt[start] = vertToAnt[end] = -1;
	}

	scanf("%d", &ants);
	for(int a = 0; a < ants; ++ a)
	{
		scanf("%d", &antToVert[a]);
		-- antToVert[a];
		state[antToVert[a]] = true;
		vertToAnt[antToVert[a]] = a;
		score[a] = 0;
	}

	scanf("%d", &ladybug);
	for(int l = 0; l < ladybug; ++ l)
	{
		scanf("%d", &landplace);
		-- landplace;
		simulate(landplace);
	}

	for(int a = 0; a < ants; ++ a)
		printf("%d %d\n", antToVert[a] + 1, score[a]);

	return 0;
}

inline static void simulate(int landing)
{
	for(int v = 0; v < verts; ++ v)
		if(vertToAnt[v] == -1)
			state[v] = false;

	directTree(landing);
	while(state[landing] != true)
	{
		moveAnts();
		floodAgainst();
	}

	++ score[vertToAnt[landing]];
}

inline static void directTree(int root)
{
	memset(moved, 0, sizeof(bool) * 1010);
	int act;
	que.push(root);
	direction[root] = -1;
	while(!que.empty())
	{
		act = que.front();
		que.pop();

		if(state[act] == true)
		{
			moved[vertToAnt[act]] = true;
			continue;
		}

		for(unsigned int n = 0; n < tree[act].size(); ++ n)
		{
			if(tree[act][n] == direction[act])
				continue;

			direction[tree[act][n]] = act;
			que.push(tree[act][n]);
		}
	}
}

inline static void moveAnts(void)
{
	for(int a = 0; a < ants; ++ a)
	{
		if(!moved[a])
			continue;

		if(state[direction[antToVert[a]]] != false)
		{
			moved[a] = false;
			continue;
		}

		state[direction[antToVert[a]]] = true;
		vertToAnt[direction[antToVert[a]]] = a;
		vertToAnt[antToVert[a]] = -1;
		antToVert[a] = direction[antToVert[a]];
	}
}

inline static void floodAgainst(void)
{
	for(int a = 0; a < ants; ++ a)
	{
		if(!moved[a])
			continue;

		floodAgainst(antToVert[a]);
	}
}

inline static void floodAgainst(int root)
{
	int act;
	que.push(root);
	while(!que.empty())
	{
		act = que.front();
		que.pop();

		for(unsigned int n = 0; n < tree[act].size(); ++ n)
		{
			if(tree[act][n] == direction[act])
				continue;

			if(state[tree[act][n]] == false)
			{
				que.push(tree[act][n]);
				state[tree[act][n]] = true;
			}
		}
	}
}
