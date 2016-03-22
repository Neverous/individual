/* 2014
 * Maciej Szeptuch
 * II UWr
 */

#include <cstdio>

int tests;
long double C, F, X,
            best;

long double count(const long double &c, const long double &f, const long double &x, int d);

int main(void)
{
    scanf("%d", &tests);
    for(int t = 0; t < tests; ++ t)
    {
        scanf("%Lf %Lf %Lf", &C, &F, &X);
        long double res = best = count(C, F, X, 0);
        for(int j = 1; res <= best; ++ j)
        {
            best = res;
            res = count(C, F, X, j);
        }

        printf("Case #%d: %.10Lf\n", t + 1, best);
    }

    return 0;
}

long double count(const long double &c, const long double &f, const long double &x, int d)
{
    long double res = x / (2.0L + d * f);
    long double ff = 0.0L;
    while(d > 0)
        ff += 1.0L / (2.0L + (--d) * f);

    return res + c * ff;
}
