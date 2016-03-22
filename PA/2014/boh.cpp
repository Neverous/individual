/* 2014
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <algorithm>

using namespace std;

int monsters,
    loss[131072], gain[131072],
    sortme[131072], s1,
    sortme2[131072], s2;
long long life;

bool gainSort(int a, int b);
bool lossSort(int a, int b);
bool check(void);

int main(void)
{
    scanf("%d %lld", &monsters, &life);
    for(int m = 0; m < monsters; ++ m)
    {
        scanf("%d %d", &loss[m], &gain[m]);
        if(gain[m] - loss[m] >= 0)
            sortme[s1 ++] = m;

        else
            sortme2[s2 ++] = m;
    }

    sort(sortme, sortme + s1, gainSort);
    sort(sortme2, sortme2 + s2, lossSort);
    if(check())
    {
        puts("TAK");
        for(int m = 0; m < s1; ++ m)
            printf("%d ", sortme[m] + 1);

        for(int m = 0; m < s2; ++ m)
            printf("%d ", sortme2[m] + 1);

        puts("");
    }

    else
        puts("NIE");

    return 0;
}

inline
bool gainSort(int a, int b)
{
    if(loss[a] < loss[b])
        return true;

    if(loss[a] > loss[b])
        return false;

    return gain[a] > gain[b];
}

inline
bool lossSort(int a, int b)
{
    if(gain[a] > gain[b])
        return true;

    if(gain[a] < gain[b])
        return false;

    return loss[a] > loss[b];
}

inline
bool check(void)
{
    // GAIN
    for(int m = 0; m < s1; ++ m)
    {
        life -= loss[sortme[m]];
        if(life <= 0)
            return false;

        life += gain[sortme[m]];
    }

    // LOSS
    for(int m = 0; m < s2; ++ m)
    {
        life -= loss[sortme2[m]];
        if(life <= 0)
            return false;

        life += gain[sortme2[m]];
    }

    return life > 0;
}
