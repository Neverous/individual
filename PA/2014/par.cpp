/* 2014
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <algorithm>

int tests,
    cars,
    height,
    ax, ay, bx, by,
    left[65536], lefts,
    right[65536], rights,
    renum[262144], r;

struct Car
{
    struct
    {
        int left;
        int right;
    } from;

    struct
    {
        int left;
        int right;
    } to;

    int height;
};

class iTree
{
    static const int SIZE = 262144;
    int data[SIZE * 2];
    int max[SIZE * 2];

    public:
        iTree(void);
        void clear(void);

        void insert(int start, int end, int value, int iStart = 0, int iEnd = SIZE - 1, int pos = 1);
        int getMax(int start, int end, int iStart = 0, int iEnd = SIZE - 1, int pos = 1);
}; // class iTree

Car car[65536];
iTree tree;

bool compareRight(int a, int b);
bool compareLeft(int a, int b);

void renumber(void);
void divide(void);

bool pathsleft(void);
bool pathsright(void);

int main(void)
{
    scanf("%d", &tests);
    for(int t = 0; t < tests; ++ t)
    {
        scanf("%d %d", &cars, &height);
        for(int c = 0; c < cars; ++ c)
        {
            scanf("%d %d %d %d", &ax, &ay, &bx, &by);
            car[c].from.left    = std::min(ax, bx);
            car[c].from.right   = std::max(ax, bx);
            car[c].height       = abs(ay - by);
        }

        for(int c = 0; c < cars; ++ c)
        {
            scanf("%d %d %d %d", &ax, &ay, &bx, &by);
            car[c].to.left  = std::min(ax, bx);
            car[c].to.right = std::max(ax, bx);
        }

        renumber();
        divide();

        puts(pathsleft() && pathsright() ? "TAK" : "NIE");
    }

    return 0;
}

inline
void renumber(void)
{
    r = 0;
    for(int c = 0; c < cars; ++ c)
    {
        renum[r ++] = car[c].from.left;
        renum[r ++] = car[c].from.right;
        renum[r ++] = car[c].to.left;
        renum[r ++] = car[c].to.right;
    }

    std::sort(renum, renum + r);
    r = std::unique(renum, renum + r) - renum;
    for(int c = 0; c < cars; ++ c)
    {
        car[c].from.left    = std::lower_bound(renum, renum + r, car[c].from.left) - renum;
        car[c].from.right   = std::lower_bound(renum + car[c].from.left, renum + r, car[c].from.right) - renum;
        car[c].to.left      = std::lower_bound(renum, renum + r, car[c].to.left) - renum;
        car[c].to.right     = std::lower_bound(renum + car[c].to.left, renum + r, car[c].to.right) - renum;
    }
}

inline
void divide(void)
{
    lefts = rights = 0;
    for(int c = 0; c < cars; ++ c)
    {
        if(car[c].to.left >= car[c].from.left)
            right[rights ++] = c;

        else
            left[lefts ++] = c;
    }

    std::sort(right, right + rights, compareRight);
    std::sort(left, left + lefts, compareLeft);
}

inline
bool pathsleft(void)
{
    tree.clear();
    for(int p = 0, c = right[0]; p < rights; c = right[++ p])
    {
        tree.insert(car[c].from.left, car[c].from.right, car[c].height);
        tree.insert(car[c].to.left, car[c].to.right, car[c].height);
    }

    for(int p = 0, c = left[0]; p < lefts; c = left[++ p])
    {
        if(car[c].height + tree.getMax(car[c].to.left + 1, car[c].from.right - 1) > height)
            return false;

        tree.insert(car[c].to.left, car[c].to.right, car[c].height);
    }

    return true;
}

inline
bool pathsright(void)
{
    tree.clear();
    for(int p = 0, c = left[0]; p < lefts; c = left[++ p])
    {
        tree.insert(car[c].from.left, car[c].from.right, car[c].height);
        tree.insert(car[c].to.left, car[c].to.right, car[c].height);
    }

    for(int p = 0, c = right[0]; p < rights; c = right[++ p])
    {
        if(car[c].height + tree.getMax(car[c].from.left + 1, car[c].to.right - 1) > height)
            return false;

        tree.insert(car[c].to.left, car[c].to.right, car[c].height);
    }

    return true;
}

inline
bool compareRight(int a, int b)
{
    return car[a].from.left > car[b].from.left;
}

inline
bool compareLeft(int a, int b)
{
    return car[a].from.right < car[b].from.right;
}

inline
iTree::iTree(void)
:data()
,max()
{
}

inline
void iTree::clear(void)
{
    for(int s = 0; s < 2 * SIZE; ++ s)
        data[s] = max[s] = 0;
}

inline
void iTree::insert(int start, int end, int value, int iStart/* = 0*/, int iEnd/* = SIZE - 1*/, int pos/* = 1*/)
{
    data[pos] = std::max(data[pos], value);
    if(start == iStart && end == iEnd)
    {
        max[pos] = std::max(max[pos], value);
        return;
    }

    int iMid = (iStart + iEnd) / 2;
    if(end <= iMid)
        return insert(start, end, value, iStart, iMid, pos * 2);

    if(start > iMid)
        return insert(start, end, value, iMid + 1, iEnd, pos * 2 + 1);

    insert(start, iMid, value, iStart, iMid, pos * 2);
    insert(iMid + 1, end, value, iMid + 1, iEnd, pos * 2 + 1);
}

inline
int iTree::getMax(int start, int end, int iStart/* = 0*/, int iEnd/* = SIZE - 1*/, int pos/* = 1*/)
{
    if(start > end)
        return 0;

    if(start == iStart && end == iEnd)
        return data[pos];

    int iMid = (iStart + iEnd) / 2;
    if(end <= iMid)
        return getMax(start, end, iStart, iMid, pos * 2);

    if(start > iMid)
        return getMax(start, end, iMid + 1, iEnd, pos * 2 + 1);

    return std::max(
        getMax(start, iMid, iStart, iMid, pos * 2),
        getMax(iMid + 1, end, iMid + 1, iEnd, pos * 2 + 1)
    );
}
