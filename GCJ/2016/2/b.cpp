/* 2016
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>

int chosen;
int people;
int tests;
long double probability[32];

long double count_probability(int choice, int p = 0, int a = 0);
long double solve(int choice = 0, int p = 0);

int main(void)
{
    scanf("%d", &tests);
    for(int t = 0; t < tests; ++ t)
    {
        scanf("%d %d", &people, &chosen);
        for(int p = 0; p < people; ++ p)
            scanf("%Lf", &probability[p]);

        printf("Case #%d: %.10Lf\n", t + 1, solve());
    }
}

long double solve(int choice, int p)
{
    if(__builtin_popcount(choice) == chosen)
        return count_probability(choice);

    if(p == people)
        return 0.0;

    long double res = solve(choice | (1 << p), p + 1);
    long double res2 = solve(choice, p + 1);
    return res > res2 ? res : res2;
}

long double count_probability(int choice, int p, int a)
{
    if((1 << p) > choice)
        return (a == chosen / 2) ? 1.0L : 0.0L;

    if(choice & (1 << p))
        return  ((a < chosen / 2) ? count_probability(choice, p + 1, a + 1) * probability[p] : 0.0L) +
                count_probability(choice, p + 1, a) * (1.0L - probability[p]);

    return count_probability(choice, p + 1, a);
}
