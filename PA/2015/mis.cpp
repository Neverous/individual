/* 2015
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <vector>

int biggest,
    cities,
    component[262144],
    count[262144],
    density,
    roads,
    start, end,
    weight[262144];
bool disabled[262144];
std::vector<int> disable,
                 graph[262144];

int markComponent(int c, const int i);

int main(void)
{
    scanf("%d %d %d", &cities, &roads, &density);
    for(int r = 0; r < roads; ++ r)
    {
        scanf("%d %d", &start, &end);
        -- start, -- end;
        ++ weight[start];
        ++ weight[end];
        graph[start].push_back(end);
        graph[end].push_back(start);
    }

    for(int c = 0; c < cities; ++ c)
        if(weight[c] < density)
        {
            disable.push_back(c);
            disabled[c] = true;
        }

    while(!disable.empty())
    {
        int cur = disable.back(); disable.pop_back();
        for(unsigned int n = 0; n < graph[cur].size(); ++ n)
        {
            -- weight[graph[cur][n]];
            if(!disabled[graph[cur][n]] && weight[graph[cur][n]] < density)
            {
                disable.push_back(graph[cur][n]);
                disabled[graph[cur][n]] = true;
            }
        }
    }

    for(int c = 0, i = 1; c < cities; ++ c)
    {
        if(disabled[c]) continue;
        if(component[c]) continue;
        count[i] = markComponent(c, i);
        if(count[i] > count[biggest])
            biggest = i;

        ++ i;
    }

    if(!biggest && count[biggest] < density)
        puts("NIE");

    else
    {
        printf("%d\n", count[biggest]);
        for(int c = 0; c < cities; ++ c)
            if(component[c] == biggest)
                printf("%d ", c + 1);

        puts("");
    }

    return 0;
}

int markComponent(int c, const int i)
{
    int result = 0;
    std::vector<int> stack;
    stack.push_back(c);
    component[c] = i;
    while(!stack.empty())
    {
        ++ result;
        int cur = stack.back(); stack.pop_back();
        for(unsigned int n = 0; n < graph[cur].size(); ++ n)
        {
            int &next = graph[cur][n];
            if(!disabled[next] && !component[next])
            {
                component[next] = i;
                stack.push_back(next);
            }
        }
    }

    return result;

}
