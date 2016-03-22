/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <cstring>

#define _x first
#define _y second
typedef std::pair<long long int, long long int> Point;

int vertices;
double dist[128][128],
       speedup[128][128];
bool inside[128][128],
     counted[128][128];
Point vert[128];

bool isCounterClockwise(void);
bool onTheLeft(const Point &a, const Point &b, const Point &c);

void countDist(void);
void checkInside(void);

double distf(const Point &a, const Point &b);
double triangulate(int from, int to);

int main(void)
{
    for(int t = 1; scanf("%d", &vertices) != -1 && vertices; ++ t)
    {
        memset(counted, 0, sizeof(bool) * 128 * 128);
        for(int v = 0; v < vertices; ++ v)
            scanf("%lld %lld", &vert[v]._x, &vert[v]._y);

        if(isCounterClockwise())
            std::reverse(vert, vert + vertices);

        countDist();
        checkInside();
        printf("Case %d: %.4lf\n", t, triangulate(0, vertices - 1));
    }

    return 0;
}

inline
bool isCounterClockwise(void)
{
    long long int area = 0;
    for(int v = 1; v < vertices; ++ v)
        area += (vert[v]._x - vert[v - 1]._x) * (vert[v]._y + vert[v - 1]._y);

    area += (vert[0]._x - vert[vertices - 1]._x) * (vert[0]._y + vert[vertices - 1]._y);
    return area < 0;
}

inline
bool onTheLeft(const Point &a, const Point &b, const Point &c)
{
    return (b._x - a._x) * (c._y - a._y) - (c._x - a._x) * (b._y - a._y) <= 0;
}

inline
double triangulate(int from, int to)
{
    if(from + 1 == to)
        return 0.0L;

    if(!inside[from][to])
        return LDBL_MAX;

    if(counted[from][to])
        return speedup[from][to];

    speedup[from][to] = LDBL_MAX;
    counted[from][to] = true;
    for(int t = from + 1; t < to; ++ t)
    {
        if(!inside[from][t] || !inside[t][to])
            continue;

        double act = triangulate(from, t) + triangulate(t, to) + ((from + 1 != t) ? dist[from][t] : 0) + ((t + 1 != to) ? dist[t][to] : 0);
        if(act < speedup[from][to])
            speedup[from][to] = act;
    }

    return speedup[from][to];
}

inline
void countDist(void)
{
    memset(dist, 0, sizeof(double) * 128 * 128);
    for(int f = 0; f < vertices; ++ f)
        for(int t = f + 1; t < vertices; ++ t)
            dist[f][t] = dist[t][f] = distf(vert[f], vert[t]);
}

inline
void checkInside(void)
{
    memset(inside, 0, sizeof(bool) * 128 * 128);
    for(int f = 0; f < vertices; ++ f)
    {
        int best = f + 1;
        inside[f][best] = inside[best][f] = true;
        for(int t = f + 2; t < vertices - 1; ++ t)
        {
            inside[f][t] = inside[t][f] = onTheLeft(vert[f], vert[best], vert[t]);
            if(!inside[f][t])
                best = t;
        }

        best = vertices - 1;
        inside[f][best] = inside[best][f] = true;
        for(int t = vertices - 2; t > f + 1; -- t)
        {
            inside[f][t] = inside[t][f] &= onTheLeft(vert[f], vert[t], vert[best]);
            if(inside[f][t])
                best = t;
        }

        inside[f][f] = false;
    }
}

inline
double distf(const Point &a, const Point &b)
{
    return sqrt((a._x - b._x) * (a._x - b._x) + (a._y - b._y) * (a._y - b._y));
}
