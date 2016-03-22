/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <vector>
#include <queue>

int t,
    verts, edges,
    start, end,
    from, to,
    opened, closed,
    travel;

std::vector<std::pair<int, int> > graph[512];
std::pair<std::pair<int, int>, int> edge[65536];

inline int shortestPath(int _from, int _to);
inline int stillOpen(const std::pair<int, int> &times, int now);
inline int nextWindow(const std::pair<int, int> &times, int now);

int main(void)
{
    while(scanf("%d %d %d %d", &verts, &edges, &start, &end) != -1)
    {
        for(int v = 0; v <= verts; ++ v)
            graph[v].clear();

        -- start; -- end;
        for(int e = 0; e < edges; ++ e)
        {
            scanf("%d %d %d %d %d", &from, &to, &opened, &closed, &travel);
            if(travel > opened)
                continue;

            -- from; -- to;
            graph[from].push_back(std::make_pair(to, e));
            edge[e] = make_pair(std::make_pair(opened, closed), travel); 
        }

        printf("Case %d: %d\n", ++ t, shortestPath(start, end));
    }
    return 0;
}

inline int shortestPath(int _from, int _to)
{
    std::priority_queue<std::pair<int, int> > que;
    int shortest[512] = {};
    for(int v = 0; v < verts; ++ v)
        shortest[v] = 1000000000;

    que.push(std::make_pair(0, _from));
    shortest[_from] = 0;
    while(!que.empty())
    {
        std::pair<int, int> act = que.top(); que.pop();
        if(act.second == _to)
            return -act.first;

        int now = -act.first;
        //printf("IN %d %d\n", now, act.second);
        for(unsigned int e = 0; e < graph[act.second].size(); ++ e)
        {
            int &dest = graph[act.second][e].first;
            //printf("TRYING TO %d\n", dest);
            std::pair<std::pair<int, int>, int> &_edge = edge[graph[act.second][e].second];
            //printf("STILL OPEN %d, NEXT WINDOW %d\n", stillOpen(_edge.first, now), nextWindow(_edge.first, now));
            if(stillOpen(_edge.first, now) >= _edge.second && shortest[dest] > now + _edge.second)
            {
                shortest[dest] = now + _edge.second;
                //printf("1. MADE IT IN %d\n", shortest[dest]);
                que.push(std::make_pair(-shortest[dest], dest));
                continue;
            }

            int window = nextWindow(_edge.first, now);
            if(shortest[dest] > window + _edge.second)
            {
                shortest[dest] = window + _edge.second;
                //printf("2. MADE IT IN %d\n", shortest[dest]);
                que.push(std::make_pair(-shortest[dest], dest));
                continue;
            }
        }
    }

    return -1;
}

inline int stillOpen(const std::pair<int, int> &times, int now)
{
    int time = now % (times.first + times.second);
    if(time <= times.first)
        return times.first - time;

    return 0;
}

inline int nextWindow(const std::pair<int, int> &times, int now)
{
    return now + times.first + times.second - (now % (times.first + times.second));
}
