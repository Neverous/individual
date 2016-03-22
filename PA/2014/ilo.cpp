/* 2014
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <algorithm>

using namespace std;

int tests,
    number,
    fib[64], fibs;

void generate(void);
bool check(int num);

int main(void)
{
    generate();
    scanf("%d", &tests);
    for(int t = 0; t < tests; ++ t)
    {
        scanf("%d", &number);
        puts(check(number) ? "TAK" : "NIE");
    }

    return 0;
}

inline
void generate(void)
{
    fib[0] = 0;
    fib[1] = 1;
    for(fibs = 2; fibs < 64 && fib[fibs - 1] <= 1000000000; ++ fibs)
        fib[fibs] = fib[fibs - 2] + fib[fibs - 1];
}

inline
bool check(int num)
{
    if(!num)
        return true;

    for(int f = 1, g = fibs - 1; f < fibs && fib[f] <= num; ++ f)
    {
        while(g > 0 && fib[g] > num / fib[f])
            -- g;

        if(num / fib[f] == fib[g] && (num % fib[f]) == 0)
            return true;
    }

    return false;
}
