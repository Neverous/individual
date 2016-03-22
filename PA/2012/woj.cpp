/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <queue>

using namespace std;

int cards,
    weight,
    a, b;
queue<int> first,
           second;
bool moves[1048576];

int main(void)
{
    scanf("%d", &cards);
    for(int p = 0, c = 1; c < cards; ++ p)
        for(int s = 0, e = (1 << p); s < e && c < cards; ++ s, ++ c)
            moves[cards - 1 - c] = (p % 2);

    //for(int c = 0; c < cards; ++ c)
    //    printf("%d ", moves[c]);

    //puts("");
    for(int c = 0; c < cards; ++ c)
    {
        scanf("%d", &weight);
        first.push(weight);
    }

    for(int c = 0; c < cards; ++ c)
    {
        scanf("%d", &weight);
        second.push(weight);
    }

    for(int c = 0; c < cards - 1; ++ c)
    {
        a = first.front(); first.pop();
        b = first.front(); first.pop();
        if(moves[c]) second.push(a > b?a:b);
        else second.push(a < b?a:b);

        a = second.front(); second.pop();
        b = second.front(); second.pop();
        if(moves[c]) first.push(a > b?a:b);
        else first.push(a < b?a:b);
    }

    //printf("%d - %d = %d\n", first.front(), second.front(), first.front() - second.front());
    printf("%d\n", first.front() - second.front());
    return 0;
}
