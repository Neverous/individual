/* 2009
 * Maciej Szeptuch
 */
#include<cstdio>
#include<vector>
#include<list>
#define abs(a) ((a) > 0?(a):-(a))
 
int tests,
    height,
    width,
    answer,
    tab[1001][1001],
    temp[1001][1001],
    p;
std::pair<int, int> points[3],
               act;
char buffer[1001];
std::list<std::pair<int, int> > que;
 
int solve(void);
void bfs(int H, int W);
 
int main(void)
{
    scanf("%d", &tests);
    for(int t = 0; t < tests; ++ t)
    {
        p = 0;
        scanf("%d %d", &height, &width);
        for(int h = 0; h < height; ++ h)
        {
            scanf("%s", buffer);
            for(int w = 0; w < width; ++ w)
            {
                tab[h][w] = -2;
                if(buffer[w] == 'X')
                    tab[h][w] = 1000000;
 
                else if(buffer[w] != '_')
                    points[p ++] = std::make_pair(h, w);
            }
        }
 
        answer = solve();
        if(answer == 1000000)
            printf("NIE\n");
 
        else
            printf("%d\n", answer);
    }
 
    return 0;
}
 
int solve(void)
{
    int min = 1000000;
    for(int P = 0; P < 3; ++ P)
    {
        for(int h = 0; h < height; ++ h)
            for(int w = 0; w < width; ++ w)
                temp[h][w] = 1000000;
 
        bfs(points[P].first, points[P].second);
        for(int h = 0; h < height; ++ h)
            for(int w = 0; w < width; ++ w)
            {
                if(tab[h][w] != 1000000)
                    tab[h][w] += temp[h][w];
            }
    }
 
    for(int h = 0; h < height; ++ h)
        for(int w = 0; w < width; ++ w)
            if(tab[h][w] < min)
                min = tab[h][w];
 
    return min;
}
 
void bfs(int H, int W)
{
    que.push_back(std::pair<int, int>(H, W));
    temp[H][W] = 0;
    while(!que.empty())
    {
        act = que.front();
        que.pop_front();
 
        for(int i = -1; i < 2; ++ i)
            for(int j = abs(i) - 1; j < 2; j += 2)
            {
                if(act.first + i < 0 ||
                   act.first + i >= height ||
                   act.second + j < 0 ||
                   act.second + j >= width ||
                   tab[act.first + i][act.second + j] == 1000000 ||
                   temp[act.first + i][act.second + j] <= temp[act.first][act.second] + 1)
                    continue;
 
                temp[act.first + i][act.second + j] = temp[act.first][act.second] + 1;
                que.push_back(std::make_pair(act.first + i, act.second + j));
            }
    }
 
    return;
}

