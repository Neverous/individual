/* 2015
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <algorithm>

void main_case(void)
{
    int first = 0;
    int second = 0;
    int rate = 0;
    int intervals = 0;
    int interval[16384]{};
    scanf("%d", &intervals);
    for(int i = 0; i < intervals; ++ i)
    {
        scanf("%d", &interval[i]);
        if(i)
        {
            first += std::max(0, interval[i - 1] - interval[i]);
            rate = std::max(rate, interval[i - 1] - interval[i]);
        }
    }

    for(int i = 0; i < intervals - 1; ++ i)
        second += std::max(std::min(rate, interval[i]), 0);

    printf("%d %d\n", first, second);
}

int main(void)
{
    int tests = 0;
    scanf("%d", &tests);
    for(int t = 0; t < tests; ++ t)
    {
        printf("Case #%d: ", t + 1);
        main_case();
    }

    return 0;
}
