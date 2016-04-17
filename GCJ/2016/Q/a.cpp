/* 2016
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>

int tests;
int number;

void solve(void);

int main(void)
{
    scanf("%d", &tests);
    for(int t = 0; t < tests; ++ t)
    {
        scanf("%d", &number);
        printf("Case #%d: ", t + 1);
        solve();
    }

    return 0;
}

void solve(void)
{
    bool found[10] = {};
    for(int i = 1; i < 128; ++ i)
    {
        int act = i * number;
        found[act % 10] = true;
        while(act)
        {
            found[act % 10] = true;
            act /= 10;
        }

        bool done = true;
        for(int d = 0; d < 10 && done; ++ d)
            done = found[d];

        if(done)
        {
            printf("%d\n", i * number);
            return;
        }
    }

    puts("INSOMNIA");
}
