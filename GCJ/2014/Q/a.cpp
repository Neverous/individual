/* 2014
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <algorithm>

int tests,
    row,
    first[4], second[4],
    same, number;

int main(void)
{
    scanf("%d", &tests);
    for(int t = 0; t < tests; ++ t)
    {
        scanf("%d", &row);
        for(int r = 1; r < row; ++ r)
            scanf("%*d %*d %*d %*d");

        scanf("%d %d %d %d", &first[0], &first[1], &first[2], &first[3]);
        for(int r = row; r < 4; ++ r)
            scanf("%*d %*d %*d %*d");

        scanf("%d", &row);
        for(int r = 1; r < row; ++ r)
            scanf("%*d %*d %*d %*d");

        scanf("%d %d %d %d", &second[0], &second[1], &second[2], &second[3]);
        for(int r = row; r < 4; ++ r)
            scanf("%*d %*d %*d %*d");

        std::sort(first, first + 4);
        std::sort(second, second + 4);
        same = 0;
        number = -1;
        for(int f = 0, s = 0; f < 4 && s < 4; ++ f)
        {
            while(s < 4 && first[f] > second[s])
                ++ s;

            if(s < 4 && first[f] == second[s])
            {
                ++ same;
                number = f;
            }
        }

        if(same == 0)
            printf("Case #%d: Volunteer cheated!\n", t + 1);

        else if(same == 1)
            printf("Case #%d: %d\n", t + 1, first[number]);

        else
            printf("Case #%d: Bad magician!\n", t + 1);
    }

    return 0;
}
