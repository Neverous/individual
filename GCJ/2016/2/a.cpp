/* 2016
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <algorithm>

int papers;
int rocks;
int rounds;
int scissors;
int tests;

bool valid(char *permutation, int size);
void solve(void);

int main(void)
{
    scanf("%d", &tests);
    for(int t = 0; t < tests; ++ t)
    {
        scanf("%d %d %d %d", &rounds, &rocks, &papers, &scissors);
        printf("Case #%d: ", t + 1);
        solve();
    }

    return 0;
}

void solve(void)
{
    char permutation[16] = {};
    for(int p = 0; p < papers; ++ p)
        permutation[p] = 'P';

    for(int r = 0; r < rocks; ++ r)
        permutation[papers + r] = 'R';

    for(int s = 0; s < scissors; ++ s)
        permutation[papers + rocks + s] = 'S';

    do
    {
        if(valid(permutation, (1 << rounds)))
        {
            puts(permutation);
            return;
        }
    }
    while(std::next_permutation(permutation, permutation + (1 << rounds)));

    puts("IMPOSSIBLE");
    return;
}

bool valid(char *permutation, int size)
{
    char result[16] = {};
    for(int s = 0; s < size; ++ s)
        result[s] = permutation[s];

    for(int s = size; s > 1; s /= 2)
    {
        for(int p = 0; p < s; p += 2)
        {
            if(result[p] == result[p + 1])
                return false;

            switch(result[p])
            {
                case 'R':
                    if(result[p + 1] == 'S')
                        result[p / 2] = 'R';

                    else
                        result[p / 2] = 'P';

                    break;

                case 'P':
                    if(result[p + 1] == 'R')
                        result[p / 2] = 'P';

                    else
                        result[p / 2] = 'S';

                    break;

                case 'S':
                    if(result[p + 1] == 'P')
                        result[p / 2] = 'S';

                    else
                        result[p / 2] = 'R';

                    break;
            }

        }
    }

    return true;
}
