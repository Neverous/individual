/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<cstring>
#include<vector>

using namespace std;

int dfs(int vert);

int verts,
    edges,
    weight[100001],
    visited[100001],
    start,
    end;

vector<int> graph[100001];

int main(void)
{
    memset(visited, -1, sizeof(int) * 100001);
    scanf("%d %d", &verts, &edges);
    for(int v = 0; v < verts; ++ v)
        scanf("%d", &weight[v+1]);
      
    for(int e = 0; e < edges; ++ e)
    {
        scanf("%d %d", &start, &end);
        graph[start].push_back(end);
    }
   
    printf("%d\n", dfs(0));
    return 0;
}

int dfs(int vert)
{
    if(visited[vert] != -1)
        return visited[vert] + weight[vert];
   
    int res;
    visited[vert] = 0;
    for(unsigned int s = 0; s < graph[vert].size(); ++ s)
    {
        res = dfs(graph[vert][s]);
        if(res > visited[vert])
            visited[vert] = res;
    }
   
    return visited[vert] + weight[vert];
}


