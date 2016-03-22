/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#include<list>
#define DEBUG(args...) fprintf(stderr, args)
//#define DEBUG(args...)

int verts,
	edges,
	start,
	end,
	size[100010],
	repr[100010],
	temp[100010];
std::vector<int> graph[100010],
				 result;
std::list<int> cons,
			   remov;
std::list<int>::iterator gimmeh[100010];

void solve(void);
int unionFind(const int &vert);
bool unionUnion(const int &a, const int &b);

int main(void)
{
	scanf("%d %d", &verts, &edges);
	for(int e = 0; e < edges; ++ e)
	{
		scanf("%d %d", &start, &end);
		-- end;
		-- start;
		graph[start].push_back(end);
		graph[end].push_back(start);
	}

	solve();
	for(std::list<int>::iterator i = cons.begin(); i != cons.end(); ++ i)
			result.push_back(size[*i]);

	printf("%d\n", (int)result.size());
	std::sort(result.begin(), result.end());
	for(unsigned int r = 0; r < result.size(); ++ r)
		printf("%d ", result[r]);

	puts("");
	return 0;
}

void solve(void)
{
	for(int v = 0; v < verts; ++ v)
	{
		repr[v] = v;
		size[v] = 1;
		cons.push_back(v);
		gimmeh[v] = --cons.end();
	}

	for(int v = 0; v < verts; ++ v)
	{
		memset(temp, 0, verts * sizeof(int));
		for(unsigned int s = 0; s < graph[v].size(); ++ s)
			++ temp[unionFind(graph[v][s])];

		for(std::list<int>::iterator i = cons.begin(); i != cons.end(); ++ i)
			if(temp[*i] < size[*i])
				unionUnion(v, *i);

		for(std::list<int>::iterator i = remov.begin(); i != remov.end(); ++ i)
			cons.erase(gimmeh[*i]);

		remov.clear();
	}

	return;
}

int unionFind(const int &vert)
{
	if(vert == repr[vert])
		return vert;

	return repr[vert] = unionFind(repr[vert]);
}

bool unionUnion(const int &a, const int &b)
{
	int fA = unionFind(a),
		fB = unionFind(b);

	if(fA == fB)
		return false;

	if(size[fA] > size[fB])
	{
		size[fA] += size[fB];
		size[fB] = 0;
		repr[fB] = fA;
		remov.push_back(fB);
	}

	else
	{
		size[fB] += size[fA];
		size[fA] = 0;
		repr[fA] = fB;
		remov.push_back(fA);
	}

	return true;
}

