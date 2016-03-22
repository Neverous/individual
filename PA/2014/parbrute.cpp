/* 2014
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <algorithm>

int tests,
    cars,
    height,
    ax, ay, bx, by;

struct Car
{
    struct
    {
        int left;
        int right;
    } from;

    struct
    {
        int left;
        int right;
    } to;

    int height;
};

Car car[65536];

bool cross(const Car &first, const Car &second);
bool solve(void);

int main(void)
{
    scanf("%d", &tests);
    for(int t = 0; t < tests; ++ t)
    {
        scanf("%d %d", &cars, &height);
        for(int c = 0; c < cars; ++ c)
        {
            scanf("%d %d %d %d", &ax, &ay, &bx, &by);
            car[c].from.left    = std::min(ax, bx);
            car[c].from.right   = std::max(ax, bx);
            car[c].height       = abs(ay - by);
        }

        for(int c = 0; c < cars; ++ c)
        {
            scanf("%d %d %d %d", &ax, &ay, &bx, &by);
            car[c].to.left  = std::min(ax, bx);
            car[c].to.right = std::max(ax, bx);
        }

        puts(solve() ? "TAK" : "NIE");
    }

    return 0;
}

inline
bool solve(void)
{
    for(int c1 = 0; c1 < cars; ++ c1)
        for(int c2 = 0; c2 < cars; ++ c2)
            if(c1 != c2 && cross(car[c1], car[c2]) && car[c1].height + car[c2].height > height)
            {
                printf("%d[%d %d -> %d %d] przecina się z %d[%d %d -> %d %d] (%d > %d)\n", c1, car[c1].from.left, car[c1].from.right, car[c1].to.left, car[c1].to.right, c2, car[c2].from.left, car[c2].from.right, car[c2].to.left, car[c2].to.right, car[c1].height + car[c2].height, height);
                return false;
            }

    return true;
}

inline
bool cross(const Car &first, const Car &second)
{
    // L2R
    if(first.from.right > second.from.left)
        return first.to.left < second.to.right;

    // R2L
    if(first.from.left < second.from.right)
        return first.to.right > second.to.left;

    return false;
}
