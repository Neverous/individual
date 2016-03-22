/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <algorithm>

int length,
    a, b, c;
char word[524288];

int main(void)
{
    scanf("%d %s", &length, word);
    for(int l = 0; l < length; ++ l)
    {
        int _a = std::min(b, c) + (word[l] != 'A'),
            _b = std::min(a, c) + (word[l] != 'B'),
            _c = std::min(a, b) + (word[l] != 'C');

        a = _a;
        b = _b;
        c = _c;
    }

    printf("%d\n", std::min(a, std::min(b, c)));
    return 0;
}
