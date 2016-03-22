/* 2014
 * Maciej Szeptuch
 * II UWr
 */

#define NDEBUG

#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

int flasks,
    steps,
    reacts,
    size,
    from[262144], to[262144];
pair<int, int> react[524288];
unordered_map<long long, int> order;
map<int, int> flask[262144];

long long $(int a, int b);
long long experiment(void);

int main(void)
{
    scanf("%d %d %d", &flasks, &steps, &reacts);
    for(int f = 0; f < flasks; ++ f)
    {
        scanf("%d", &size);
        flask[f][f] = size;
    }

    for(int s = 0; s < steps; ++ s)
    {
        scanf("%d %d", &from[s], &to[s]);
        -- from[s], -- to[s];
    }

    for(int r = 0; r < reacts; ++ r)
    {
        scanf("%d %d", &react[r].first, &react[r].second);
        -- react[r].first, -- react[r].second;
        if(react[r].first > react[r].second)
            swap(react[r].first, react[r].second);

        order[$(react[r].first, react[r].second)] = r;
    }

    printf("%lld\n", experiment());
    return 0;
}

inline
long long $(int a, int b)
{
    return ((1LL * a) << 32) + b;
}

inline
long long experiment(void)
{
    long long sediment = 0;
    for(int s = 0; s < steps; ++ s)
    {
        auto &_from = flask[from[s]];
        auto &_to   = flask[to[s]];

#ifndef NDEBUG
        printf("mixing %d with %d\n", from[s], to[s]);
        printf("%d: ", from[s]);
        for(const auto &f: _from)
            printf("%d(%d) ", f.first, f.second);

        printf("\n%d: ", to[s]);
        for(const auto &t: _to)
            printf("%d(%d) ", t.first, t.second);

        puts("\n---");
#endif // NDEBUG

        vector<int> reacting;
        for(const auto &f: _from)
            for(const auto &t: _to)
            {
                long long _hash = f.first < t.first ? $(f.first, t.first) : $(t.first, f.first);
                if(order.count(_hash))
                    reacting.push_back(order[_hash]);
            }

        sort(begin(reacting), end(reacting));
        reacting.erase(unique(begin(reacting), end(reacting)), end(reacting));

        for(const auto &r: reacting)
        {
            if(_from.count(react[r].first) && _to.count(react[r].second))
            {
                int count = min(_from[react[r].first], _to[react[r].second]);
                sediment += count * 2;
                _from[react[r].first] -= count;
                _to[react[r].second] -= count;
            }

            if(_from.count(react[r].second) && _to.count(react[r].first))
            {
                int count = min(_from[react[r].second], _to[react[r].first]);
                sediment += count * 2;
                _from[react[r].second] -= count;
                _to[react[r].first] -= count;
            }
        }

        map<int, int> next;
        for(const auto &f: _from)
            if(f.second > 0)
                next[f.first] += f.second;

        for(const auto &t: _to)
            if(t.second > 0)
                next[t.first] += t.second;

        _from.clear();
        _to = next;
    }

    return sediment;
}
