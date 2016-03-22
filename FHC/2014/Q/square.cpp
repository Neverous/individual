/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>

int tests,
    size;
char row[32][32];

bool solve(void);

int main(void)
{
    scanf("%d", &tests);
    for(int t = 0; t < tests; ++ t)
    {
        scanf("%d", &size);
        for(int h = 0; h < size; ++ h)
            scanf("%s", row[h]);

        printf("Case #%d: %s\n", t + 1, solve() ? "YES" : "NO");
    }

    return 0;
}

bool solve(void)
{
    bool found = false;
    int h = 0,
        w = 0,
        length = 0;

    for(h = 0; !found && h < size; ++ h)
        for(w = 0; !found && w < size; ++ w)
            found = row[h][w] == '#';

    if(!found)
        return false;

    -- h, -- w;
    for(int s = 0; w + s < size && row[h][w + s] == '#'; ++ s)
        ++ length;

    for(int s = 0; s < length; ++ s)
    {
        for(int x = 0; x < w; ++ x)
            if(row[h + s][x] == '#')
                return false;

        for(int x = 0; x < length; ++ x)
            if(row[h + s][w + x] != '#')
                return false;

        for(int x = w + length; x < size; ++ x)
            if(row[h + s][x] == '#')
                return false;
    }

    for(h += length; h < size; ++ h)
        for(w = 0; w < size; ++ w)
            if(row[h][w] == '#')
                return false;

    return true;
}
