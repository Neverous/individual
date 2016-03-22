/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <algorithm>

const int TREE_SIZE = 131072;

class Tree
{
    int min[TREE_SIZE * 2],
        data[TREE_SIZE * 2];
    public:
        Tree(void):min(), data() {}
        void init(void);
        void add(int start, int end, int iStart = 1, int iEnd = TREE_SIZE, int pos = 1);
        int getCount(int level, int pos = 1, int result = TREE_SIZE);
};

inline int MIN(int a, int b){return a<b?a:b;}

int t,
    bridges,
    raises,
    flooded,
    act, from, to;

Tree tree;

int main(void)
{
    while(scanf("%d %d %d", &bridges, &raises, &flooded) != -1)
    {
        int height[TREE_SIZE] = {};
        for(int b = 0; b < bridges; ++ b)
            scanf("%d", &height[b]);

        std::sort(height, height + TREE_SIZE);
        tree.init();
        act = 1;
        for(int r = 0; r < raises; ++ r)
        {
            scanf("%d %d", &from, &to);
            //printf("%d => %zu, %d => %zu\n", act, std::lower_bound(height, height + TREE_SIZE, act) - height,
            //                               from, std::upper_bound(height, height + TREE_SIZE, from) - height - 1);
            tree.add(std::lower_bound(height, height + TREE_SIZE, act) - height, std::upper_bound(height, height + TREE_SIZE, from) - height - 1);
            act = to + 1;
        }

        printf("Case %d: %d\n", ++ t, tree.getCount(flooded));
    }

    return 0;
}

void Tree::init(void)
{
    for(int p = 0; p < TREE_SIZE * 2; ++ p)
        min[p] = data[p] = 0;
}

void Tree::add(int start, int end, int iStart/* = 1*/, int iEnd/* = TREE_SIZE*/, int pos/* = 1*/)
{
    if(start > end)
        return;

    //printf("IN (%d, %d) [%d, %d] {%d}\n", start, end, iStart, iEnd, pos);
    if(start == iStart && end == iEnd)
    {
        data[pos] += 1;
        min[pos] += 1;
        return;
    }

    int iMiddle = (iStart + iEnd) / 2;
    if(end <= iMiddle)
        add(start, end, iStart, iMiddle, pos * 2);

    else if(start > iMiddle)
        add(start, end, iMiddle + 1, iEnd, pos * 2 + 1);

    else
    {
        add(start, iMiddle, iStart, iMiddle, pos * 2);
        add(iMiddle + 1, end, iMiddle + 1, iEnd, pos * 2 + 1);
    }

    min[pos] = MIN(min[pos * 2], min[pos * 2 + 1]) + data[pos];
}

int Tree::getCount(int level, int pos/* = 1*/, int result/* = TREE_SIZE*/)
{
    if(min[pos] >= level)
        return result;

    if(pos > TREE_SIZE)
        return 0;

    return getCount(level - data[pos], pos * 2, result / 2) + getCount(level - data[pos], pos * 2 + 1, result / 2);
}
