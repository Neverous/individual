/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>

int characters;
char line[64];

int main(void)
{
    scanf("%d", &characters);
    scanf("%*s %*s %*s %s %*s", line);
    for(int c = 0; c < characters; ++ c)
        if(line[c*4 + 1] == '*')
            putchar('1');

        else if(line[c*4] == '*')
            putchar('2');

        else
            putchar('3');

    puts("");
    return 0;
}
