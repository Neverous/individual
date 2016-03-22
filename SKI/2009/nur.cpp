/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
*/
#include<cstdio>
#include<vector>
#include<algorithm>
#define in_interval(a,b) ((a) >= (b).first && (a) <= (b).second)
#define lt_interval(a,b) ((a).second - (a).first < (b).second - (b).first)

using namespace std;

pair<int, pair<int, int> > edge[1000001];
pair<int, int> interval[1000001];
int verts,
	edges,
	unionTab[1000001],
	questions,
	from,
	to,
	time,
	dfsCount = 1;
vector<pair<int, int> > graph[1000001];

int unionFind(int &vert); // Union - find
inline bool unionUnion(int &a, int &b); // Union - union
inline void findMST(pair<int, pair<int, int> > *edge, int &edges); // Znajdź MST
void specialDfs(int &vert); // specialDFS
inline bool solve(int &from, int &to, int &time); // Sprawdź czy się da...
bool findDFS(int &vert, int &search, int &time); // Czy da się dotrzeć... 

int main(void)
{
	scanf("%d %d", &verts, &edges);
	for(int e = 0; e < edges; ++ e)
		scanf("%d %d %d", &edge[e].second.first, &edge[e].second.second, &edge[e].first);

	sort(edge, edge + edges);

	/* MINIMALNE DRZEWO SPINAJĄCE - MOŻE DA JAKIEGOŚ SPEED UP`A */
	findMST(edge, edges);

	/* ZBUDUJ GRAF Z TEGO CO ZOSTAŁO */
	for(int e = 0; e < edges; ++ e)
	{
		graph[edge[e].second.first].push_back(pair<int, int>(edge[e].second.second, edge[e].first));
		graph[edge[e].second.second].push_back(pair<int, int>(edge[e].second.first, edge[e].first));
	}

	/* PUŚĆ SOBIE DFS */
	for(int v = 1; v <= verts; ++ v)
		if(!interval[v].first)
			specialDfs(v);

	scanf("%d", &questions);
	for(int q = 0; q < questions; ++ q)
	{
		scanf("%d %d %d", &from, &to, &time);
		printf("%s\n", solve(from, to, time)?"TAK":"NIE");
	}

	return 0;
}

int unionFind(int &vert)
{
	if(unionTab[vert] != vert)
		unionTab[vert] = unionFind(unionTab[vert]);

	return unionTab[vert];
}
inline bool unionUnion(int &a, int &b)
{
	int proxyA = unionFind(a),
		proxyB = unionFind(b);

	if(proxyA == proxyB)
		return false;

	if(proxyA > proxyB)
		unionTab[proxyA] = proxyB;

	else
		unionTab[proxyB] = proxyA;

	return true;
}

inline void findMST(pair<int, pair<int, int> > *edge, int &edges)
{
	for(int v = 1; v <= verts; ++ v)
		unionTab[v] = v;

	for(int e = 0; e < edges; ++ e)
	{
		if(!unionUnion(edge[e].second.first, edge[e].second.second))
			edge[e].first = -1;
	}

	int newPos = 0;
	for(int e = 0; e < edges; ++ e, ++ newPos)
	{
		if(edge[e].first < 0)
		{
			-- newPos;
			continue;
		}

		if(newPos != e)
			edge[newPos] = edge[e];
	}

	edges = newPos;
	return;
}

void specialDfs(int &vert)
{
	if(interval[vert].first)
		return;

	interval[vert].first = dfsCount ++;
	for(unsigned int s = 0; s < graph[vert].size(); ++ s)
		if(!interval[graph[vert][s].first].first)
			specialDfs(graph[vert][s].first);

	interval[vert].second = dfsCount;
	return;
}

inline bool solve(int &from, int &to, int &time)
{
	if(time < edge[0].first)
		return false;

	if(unionFind(from) != unionFind(to))
		return false;

	if(time > edge[edges - 1].first)
		return true;

	return findDFS(from, to, time);
}

bool findDFS(int &vert, int &search, int &time)
{
	if(vert == search)
		return true;

	bool found = false;
	for(unsigned int s = 0; s < graph[vert].size(); ++ s)
	{
		if(lt_interval(interval[graph[vert][s].first], interval[vert]) && 
				in_interval(interval[search].first, interval[graph[vert][s].first]))
		{
			found = true;
			if(graph[vert][s].second <= time)
				return findDFS(graph[vert][s].first, search, time);
		}
	}

	if(found)
		return false;

	for(unsigned int s = 0; s < graph[vert].size(); ++ s)
		if(graph[vert][s].second <= time &&
				lt_interval(interval[vert], interval[graph[vert][s].first]))
			return findDFS(graph[vert][s].first, search, time);

	return false;

}


