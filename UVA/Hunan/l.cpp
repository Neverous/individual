/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <vector>

int problems,
    teams,
    submissions,
    time,
    team;
char problem[2],
     verdict[4];
bool solved[128][16];
std::pair<int, int> answer[16];

int main(void)
{
    scanf("%d %d %d", &problems, &teams, &submissions);
    for(int s = 0; s < submissions; ++ s)
    {
        scanf("%d %d %s %s", &time, &team, problem, verdict);
        if(verdict[0] == 'N')
            continue;

        if(solved[team][problem[0] - 'A'])
            continue;

        solved[team][problem[0] - 'A'] = true;
        answer[problem[0] - 'A'] = std::make_pair(time, team);
    }

    for(int p = 0; p < problems; ++ p)
    {
        putchar('A' + p);
        if(!answer[p].second)
            puts(" - -");

        else
            printf(" %d %d\n", answer[p].first, answer[p].second);
    }

    return 0;
}
