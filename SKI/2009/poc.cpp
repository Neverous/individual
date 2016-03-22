/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
#define NAME(a) (names + positions[(a) - 1] + 1)
#define TEMPLATE(a) (templat + tpos[(a) - 1] + 1)
 
using namespace std;
 
vector<int> graph[100010];
char names[11000100],
	 templat[11000100],
	 name[1001],
	 sType[8];
int positions[100010],
	tpos[100010],
	verts,
	questions,
	parent,
	size,
	visited[100010];
bool type[100010];
 
inline bool solve(int size);
bool dfs(int vert, int tt, int flag, int father);
 
int main(void)
{
	scanf("%d", &verts);
	scanf("%s", names);
	positions[0] = -1;
	positions[1] = strlen(names);
	for(int v = 2; v <= verts; ++ v)
	{
		scanf("%d %s", &parent, NAME(v));
		graph[parent].push_back(v);
		graph[v].push_back(parent);
		positions[v] = positions[v - 1] + 1 + strlen(NAME(v));
	}
 
	scanf("%d", &questions);
	for(int q = 0; q < questions; ++ q)
	{
		scanf("%d", &size);
		printf("%s\n", solve(size)?"TAK":"NIE");
	}
	return 0;
}
 
inline bool solve(int size)
{
	scanf("%s", templat);
	memset(visited, 0, 100010 * sizeof(int));
	tpos[0] = -1;
	tpos[1] = strlen(templat);
	for(int v = 2; v <= size; ++ v)
	{
		scanf("%s %s", sType, TEMPLATE(v));
		tpos[v] = tpos[v - 1] + 1 + strlen(TEMPLATE(v));
		type[v] = !strcmp(sType, "SYN");
	}
 
	if(strcmp(NAME(1), TEMPLATE(1)))
		return false;
 
	return dfs(1, 1, 1, -1);
}
 
bool dfs(int vert, int tt, int flag, int father)
{
	if(visited[vert] == flag)
		return false;
 
	bool offspring = false;
	visited[vert] = flag;
	if(!strcmp(NAME(vert), TEMPLATE(tt)))
	{
		offspring = true;
		++ tt;
	}
 
	if(tt > size)
		return true;
 
	bool tmp = false;
	if(type[tt])
	{
		for(unsigned int s = 0; s < graph[vert].size(); ++ s)
			if(!strcmp(NAME(graph[vert][s]), TEMPLATE(tt)))
			{
				if(graph[vert][s] == father)
					continue;

				if(tt > size)
					return true;
 
				tmp = dfs(graph[vert][s], tt, flag, vert);
				if(tmp)
					return true;
			}
	}
	else
	{
		for(unsigned int s = 0; s < graph[vert].size(); ++ s)
		{
			if(graph[vert][s] == father)
				continue;

			tmp = dfs(graph[vert][s], tt, flag, vert);
			if(tmp)
				return true;
		}
	}

	if(offspring)
	{
		for(unsigned int s = 0; s < graph[vert].size(); ++ s)
		{
			if(graph[vert][s] == father)
				continue;

			tmp = dfs(graph[vert][s], tt - 1, flag + 1, vert);
			if(tmp)
				return true;
		}
	}
 
	return false;
}

