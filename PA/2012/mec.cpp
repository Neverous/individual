/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <set>

using namespace std;

int games,
    people,
    number;
long long int player[65536];
char useless[524288];
set<long long int> speed;

inline const bool solve(void);  

int main(void)
{
    scanf("%d %d", &people, &games);
    for(int g = 0; g < games; ++ g)
    {
        for(int p = 0; p < people / 2; ++ p)
        {
            scanf("%d", &number);
            player[-- number] |= (1LL << g);
        }

        scanf("%[^\n]s", useless);
    }

    puts(solve() ? "TAK" : "NIE");
    return 0;
}

inline const bool solve(void)
{
    for(int p = 0; p < people; ++ p)
        if(!speed.insert(player[p]).second)
            return false;

    return true;
}
