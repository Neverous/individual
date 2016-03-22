/* 2013
 * Maciej Szeptuch
 * IIUWr
 */
#include <cstdio>
#include <cstring>

int tests,
    height, width,
    res1[512][512],
    res2[512][512],
    result;
char row[512][512];

inline int MAX(int a, int b) { return a>b?a:b; }

int main(void)
{
    scanf("%d", &tests);
    for(int t = 0; t < tests; ++ t)
    {
        memset(res1, 0, 512 * 512 * sizeof(int));
        memset(res2, 0, 512 * 512 * sizeof(int));
        res1[1][1] = 1;
        scanf("%d %d", &height, &width);
        for(int h = 1; h <= height; ++ h)
        {
            scanf("%s", row[h]);
            for(int w = 1; w <= width; ++ w) if(row[h][w - 1] == '.')
            {
                if(res1[h-1][w] > 0)
                    res1[h][w] = MAX(res1[h][w], res1[h-1][w] + 1);

                if(res1[h][w-1] > 0)
                    res1[h][w] = MAX(res1[h][w], res1[h][w-1] + 1);
            }
        }

        for(int h = height; h > 0; -- h)
            for(int w = width; w > 0; -- w) if(row[h][w-1] == '.')
                res2[h][w] = MAX(res2[h][w], MAX(res2[h+1][w], res2[h][w+1]) + 1);

        result = 0;
        for(int h = 1; h <= height; ++ h)
            for(int w = 1; w <= width; ++ w)
            {
                result = MAX(result, res1[h][w]);
                if(h > 1) for(int f = w; f > 0 && row[h][f-1] == '.'; -- f)
                    if(row[h-1][w-1] == '.' && row[h+1][f-1] == '.') result = MAX(result, res1[h-1][w] + res2[h+1][f] + w - f + 1);
            }

        for(int w = 1; w <= width; ++ w)
            for(int h = 1; h <= height; ++ h)
            {
                result = MAX(result, res1[h][w]);
                if(w > 1) for(int j = h; j > 0 && row[j][w-1] == '.'; -- j)
                    if(row[h][w-2] == '.' && row[j][w] == '.') result = MAX(result, res1[h][w-1] + res2[j][w+1] + h - j + 1);
            }

        printf("Case #%d: %d\n", t + 1, result);
    }

    return 0;
}
