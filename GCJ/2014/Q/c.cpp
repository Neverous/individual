/* 2014
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <algorithm>

int tests,
    R, C, M,
    visited[2500],
    f = 0;

void printSolution(int *map);
bool move(int *map, int p);
int count(int *map, int p);
void solve(void);

int main(void)
{
    scanf("%d", &tests);
    for(int t = 0; t < tests; ++ t)
    {
        scanf("%d %d %d", &R, &C, &M);
        printf("Case #%d:\n", t + 1);
        solve();
    }

    return 0;
}

inline
void solve(void)
{
    int map[2500] = {};
    for(int p = 0; p < M; ++ p)
        map[R * C - 1 - p] = 1;

    do
    {
        for(int p = 0; p < R * C; ++ p)
            if(!map[p])
            {
                ++ f;
                if(count(map, p) == R * C - M)
                {
                    map[p] = 2;
                    printSolution(map);
                    return;
                }
            }
    }
    while(std::next_permutation(map, map + R * C));

    puts("Impossible");
    return;
}

inline
int count(int *map, int p)
{
    int cnt = 1;
    visited[p] = f;
    if(move(map, p))
        for(int i = -1; i < 2; ++ i)
            for(int j = -1; j < 2; ++ j)
                if( 0 <= p % C + i && p % C + i < C &&
                    0 <= p / C + j && p / C + j < R &&
                    visited[p + i + j * C] != f &&
                    map[p + i + j * C] == 0)
                    cnt += count(map, p + i + j * C);

    return cnt;
}

inline
bool move(int *map, int p)
{
    int cnt = 0;
    for(int h = std::max(p / C - 1, 0); h < std::min(p / C + 2, R); ++ h)
        for(int w = std::max(p % C - 1, 0); w < std::min(p % C + 2, C); ++ w)
            cnt += map[h * C + w];

    return cnt == 0;
}

inline
void printSolution(int *map)
{
    for(int h = 0; h < R; ++ h)
    {
        for(int w = 0; w < C; ++ w)
            switch(map[h * C + w])
            {
                case 0:
                    putchar('.');
                    break;

                case 1:
                    putchar('*');
                    break;

                case 2:
                    putchar('c');
                    break;
            }

        puts("");
    }

    return;
}
