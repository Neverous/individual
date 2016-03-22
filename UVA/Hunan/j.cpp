/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>

int start,
    end,
    t;
int rest[10] = {1, 8, 7, 4, 5, 6, 3, 2, 9, 0};

inline int count(int st, int en);

int main(void)
{
    while(scanf("%d %d", &start, &end) != -1)
        printf("Case %d: %d\n", ++ t, count(start, end)); 

    return 0;
}

inline int count(int st, int en)
{
    int result = 0;
    for(int a = st; a <= en && a * a * a <= en * 10 + 3; ++ a)
        for(int b = st; b <= en && a * a * a + b * b * b <= en * 10 + 3; ++ b)
        {
            int res = a * a * a + b * b * b;
            if(res % 10 != 3 || res / 10 < st || res / 10 > en)
                continue;

            ++ result;
        }

    return result;
}
