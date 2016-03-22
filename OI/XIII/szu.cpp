/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<queue>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int verts,
	edges,
	from,
	to,
	act;
unsigned short int result;
std::vector<unsigned short int> paths;
std::vector<bool> visited,
				  checked;
std::vector<std::vector<int> > reversed;
std::vector<int> resultVerts,
				 level;
std::queue<int> que;

int main(void)
{
	scanf("%d %d", &verts, &edges);
	reversed.resize(verts + 1);
	level.resize(verts + 1);
	paths.resize(verts + 1);
	visited.resize(verts + 1);
	checked.resize(verts + 1);
	for(int v = 0; v <= verts; ++ v)
		paths[v] = 0;

	paths[verts] = 1;
	for(int e = 0; e < edges; ++ e)
	{
		scanf("%d %d", &from, &to);
		reversed[to - 1].push_back(from - 1);
		++ level[from - 1];
	}

	que.push(verts);
	visited[verts] = true;
	while(!que.empty())
	{
		act = que.front();
		que.pop();

		for(unsigned int n = 0; n < reversed[act].size(); ++ n)
			if(!visited[reversed[act][n]])
			{
				visited[reversed[act][n]] = true;
				que.push(reversed[act][n]);
			}
	}

	for(int v = 0; v <= verts; ++ v)
		if(!visited[v])
			for(unsigned int n = 0; n < reversed[v].size(); ++ n)
				-- level[reversed[v][n]];

	for(int v = 0; v <= verts; ++ v)
		if(!level[v])
			que.push(v);

	while(!que.empty())
	{
		act = que.front();
		que.pop();
		checked[act] = true;
		if(!visited[act])
			continue;

		for(unsigned int n = 0, v; n < reversed[act].size(); ++ n)
		{
			v = reversed[act][n];
			-- level[v];
			if((int)paths[v] + paths[act] > 36501)
				paths[v] = 36501;

			else
				paths[v] += paths[act];

			if(!level[v])
				que.push(v);
		}
	}

	for(int v = 0; v < verts; ++ v)
		if(visited[v] && !checked[v])
			paths[v] = 36501;

	for(int v = 0; v < verts; ++ v)
	{
		if(!visited[v])
			continue;

		if(paths[v] > result)
		{
			result = paths[v];
			resultVerts.clear();
		}

		if(paths[v] == result)
			resultVerts.push_back(v + 1);
	}

	if(result > 36500)
		puts("zawsze");

	else
		printf("%d\n", result);

	printf("%d\n", (int)resultVerts.size());
	for(unsigned int r = 0; r < resultVerts.size(); ++ r)
		printf("%d%c", resultVerts[r], r + 1 == resultVerts.size()?'\n':' ');

	return 0;
}

