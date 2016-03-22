/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>

int width,
    length,
    side[1048576],
    cnt[1048576],
    front,
    sideMax, frontMax;
long long int sum[1048576],
              res;

int main(void)
{
    scanf("%d %d", &width, &length);
    for(int w = 0; w < width; ++ w)
    {
        scanf("%d", &side[w]);
        if(sideMax < side[w])
            sideMax = side[w];
    }

    for(int l = 0; l < length; ++ l)
    {
        scanf("%d", &front);
        if(frontMax < front)
            frontMax = front;

        sum[front] += front;
        ++ cnt[front];
    }

    if(frontMax != sideMax)
    {
        puts("NIE");
        return 0;
    }

    for(int n = 1; n < 1048576; ++ n)
    {
        cnt[n] += cnt[n - 1];
        sum[n] += sum[n - 1];
    }

    for(int w = 0; w < width; ++ w)
        res += sum[side[w]] + 1LL * (length - cnt[side[w]]) * side[w];

    printf("%lld\n", res);
    return 0;
}
