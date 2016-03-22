/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <vector>
#include <queue>

int t,
    start,
    end,
    append[10],
    add[10],
    multiply[10];

std::pair<int, int> shortestPath(int from, int to);

int main(void)
{
    while(scanf("%d %d", &start, &end) != -1)
    {
        for(int a = 0; a < 10; ++ a)
            scanf("%d", &append[a]);

        for(int a = 0; a < 10; ++ a)
            scanf("%d", &add[a]);

        for(int m = 0; m < 10; ++ m)
            scanf("%d", &multiply[m]);

        std::pair<int, int> res = shortestPath(start, end);
        printf("Case %d: %d %d\n", ++ t, res.first, res.second);
    }

    return 0;
}

std::pair<int, int> shortestPath(int from, int to)
{
    std::priority_queue<std::pair<std::pair<int, int>, int> > que;
    que.push(std::make_pair(std::make_pair(0, 0), from));
    std::pair<int, int> shortest[131072];
    for(int s = 0; s < 131072; ++ s)
        shortest[s].first = shortest[s].second = 1000000000;

    shortest[from].first = shortest[from].second = 0;
    while(!que.empty())
    {
        std::pair<int, int> cost = que.top().first; cost.first *= -1; cost.second *= -1;
        int pos = que.top().second;
        que.pop();

        if(pos == to)
            return cost;

        for(int a = 0; a < 10; ++ a)
        {
            int next = pos * 10 + a;
            std::pair<int, int> nextCost = cost;
            nextCost.first += append[a];
            ++ nextCost.second;
            if(next > to || shortest[next] <= nextCost) continue;
            shortest[next] = nextCost;
            nextCost.first *= -1;
            nextCost.second *= -1;
            que.push(std::make_pair(nextCost, next));
        }

        for(int a = 0; a < 10; ++ a)
        {
            int next = pos + a;
            std::pair<int, int> nextCost = cost;
            nextCost.first += add[a];
            ++ nextCost.second;
            if(next > to || shortest[next] <= nextCost) continue;
            shortest[next] = nextCost;
            nextCost.first *= -1;
            nextCost.second *= -1;
            que.push(std::make_pair(nextCost, next));
        }

        for(int m = 0; m < 10; ++ m)
        {
            int next = pos * m;
            std::pair<int, int> nextCost = cost;
            nextCost.first += multiply[m];
            ++ nextCost.second;
            if(next > to || shortest[next] <= nextCost) continue;
            shortest[next] = nextCost;
            nextCost.first *= -1;
            nextCost.second *= -1;
            que.push(std::make_pair(nextCost, next));
        }
    }

    return std::make_pair(-1, -1);
}
