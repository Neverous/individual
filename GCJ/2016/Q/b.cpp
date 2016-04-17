/* 2016
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <algorithm>

int tests;
char setting[128];

int main(void)
{
    scanf("%d", &tests);
    for(int t = 0; t < tests; ++ t)
    {
        scanf("%s", setting);
        int len = 0; while(setting[len]) ++ len;
        int blocks = 0;
        for(int s = 0; setting[s]; ++ s)
            blocks += !s || setting[s] != setting[s - 1];

        blocks -= setting[len - 1] == '+';
        printf("Case #%d: %d\n", t + 1, blocks);
    }

    return 0;
}
