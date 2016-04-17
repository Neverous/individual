/* 2016
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>

int generation;
int size;
int students;
int tests;

int main(void)
{
    scanf("%d", &tests);
    for(int t = 0; t < tests; ++ t)
    {
        scanf("%d %d %d", &size, &generation, &students);
        printf("Case #%d: ", t + 1);
        for(int s = 0; s < size; ++ s)
            printf("%d ", s + 1);

        puts("");
    }

    return 0;
}
