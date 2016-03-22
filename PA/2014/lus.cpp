/* 2014
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <algorithm>

using namespace std;

int tests,
    companies,
    wMin, wMax,
    hMin, hMax,
    ws[131072], we[131072],
    hs[131072], he[131072];

bool check(void);

int main(void)
{
    scanf("%d", &tests);
    for(int t = 0; t < tests; ++ t)
    {
        scanf("%d", &companies);
        wMin = hMin = 1000000001;
        wMax = hMax = 0;
        for(int c = 0; c < companies; ++ c)
        {
            scanf("%d %d %d %d", &ws[c], &we[c], &hs[c], &he[c]);
            wMin = min(ws[c], wMin);
            wMax = max(we[c], wMax);
            hMin = min(hs[c], hMin);
            hMax = max(he[c], hMax);
        }

        puts(check() ? "TAK" : "NIE");
    }
}

inline
bool check(void)
{
    for(int c = 0; c < companies; ++ c)
        if( ws[c] == wMin
        &&  we[c] == wMax
        &&  hs[c] == hMin
        &&  he[c] == hMax)
            return true;

    return false;
}
