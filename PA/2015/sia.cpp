/* 2015
 * Maciej Szeptuch
 * II UWr
 */
#include <algorithm>
#include <cstdio>
#include <tuple>

typedef long long int               llu;
typedef std::tuple<int, llu, llu>   Mow; // idx, size, day

int area,
    growth[524288],
    idx[524288],
    mowings;

llu day,
    size,
    sum[524288];

Mow mowing[524288];

int main(void)
{
    scanf("%d %d", &area, &mowings);
    for(int a = 0; a < area; ++ a)
    {
        scanf("%d", &growth[a]);
        idx[a+1] = a+1;
    }

    std::sort(growth, growth + area);
    for(int a = 0; a < area; ++ a)
        sum[a + 1] = sum[a] + growth[a];


    int m = 0;
    for(int _ = 0; _ < mowings; ++ _)
    {
        scanf("%lld %lld", &day, &size);
        int a = *std::lower_bound(idx, idx + area, size, [m](int id, llu)
        {
            auto mow = *(std::upper_bound(
                mowing,
                mowing + m + 1,
                std::make_tuple(id + 1, 0L, 0L)) - 1);

            return std::get<1>(mow) + \
                   (day - std::get<2>(mow)) * growth[id] <= size;
        });

        auto mowit = std::upper_bound(
            mowing,
            mowing + m + 1,
            Mow{a + 1, 0L, 0L}) - 1;
        auto mow = *mowit;
        auto mow1 = *++mowit;

        llu result = 0;
        int b = a;
        while(b < area)
        {
            if(mowit != mowing + m + 1)
            {
                result += (sum[std::get<0>(mow1)] - sum[b]) * (day - std::get<2>(mow)) + \
                          (std::get<1>(mow) - size) * (std::get<0>(mow1) - b);

                b = std::get<0>(mow1);
            }

            else
            {
                result += (sum[area] - sum[b]) * (day - std::get<2>(mow)) + \
                          (std::get<1>(mow) - size) * (area - b);
                break;
            }

            mow = mow1;
            mow1 = *++mowit;
        }

        printf("%lld\n", result);
        while(m && std::get<0>(mowing[m]) >= a)
            -- m;

        mowing[++ m] = Mow{a, size, day};
    }

    return 0;
}
