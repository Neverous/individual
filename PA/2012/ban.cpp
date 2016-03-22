/* 2012
 * Maciej Szeptuch
 * II UWr
 */

#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int people,
    start, end,
    res;
vector<pair<int, int> > points;

int main(void)
{
    scanf("%d", &people);
    for(int p = 0; p < people; ++ p)
    {
        scanf("%d %d", &start, &end);
        if(start == end) continue;
        points.push_back(make_pair(start, end));
        points.push_back(make_pair(end, start));
    }

    sort(points.begin(), points.end());
    for(int p = 0, act = 0, mx = 0; p < points.size(); ++ p)
    {
        if(points[p].first > points[p].second && (!mx || mx < act))
        {
            res = max(res, act);
            mx = max(mx, act);
            for(int p2 = p + 1, en = 0, act2 = act; p2 < points.size(); ++ p2)
            {
                if(points[p2].first > points[p2].second)
                {
                    res = max(res, act2 + en);
                    //printf(">>>act:%d act2:%d en:%d res:%d\n", act, act2, en, res);
                    if(points[p2].second < points[p].first) ++ en;
                }

                act2 += points[p2].first > points[p2].second ? -1: 1;
            }
        }

        act += points[p].first > points[p].second ? -1: 1;
    }

    printf("%d\n", res);
    return 0;
}
