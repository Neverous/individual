/* 2014
 * Maciej Szeptuch
 * II UWr
 */
//#define NDEGBUG

#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstring>
#include <functional>

using namespace std;

typedef vector<int> Array;

#pragma pack(push)
struct Rectangle
{
    int left;
    int right;
    int top;
    int bottom;

    bool operator<(const Rectangle &rect) const;
}; // struct Rectangle
#pragma pack(pop)

int         rectangles;
Rectangle   rectangle[131072];
Array       mapping;

void renumber(void);
void derenumber(void);

void solve(void);
bool intersects(const Rectangle &A, const Rectangle &B);
void join(Rectangle &dst, const Rectangle &src);

int main(void)
{
    scanf("%d", &rectangles);
    for(int r = 0; r < rectangles; ++ r)
        scanf("%d %d %d %d", &rectangle[r].left, &rectangle[r].right, &rectangle[r].bottom, &rectangle[r].top);

    renumber();

    solve();

    derenumber();

    printf("%d\n", rectangles);
    for(int r = 0; r < rectangles; ++ r)
        printf("%d %d %d %d\n", rectangle[r].left, rectangle[r].right, rectangle[r].bottom, rectangle[r].top);

    return 0;
}

inline
void renumber(void)
{
    mapping.resize(rectangles * 4);
    memcpy(&mapping[0], &rectangle[0].left, sizeof(int) * 4 * rectangles);

    sort(begin(mapping), end(mapping));
    mapping.erase(unique(begin(mapping), end(mapping)), end(mapping));

    transform(&rectangle[0].left, &rectangle[rectangles].left, &rectangle[0].left,
        bind(distance<Array::iterator>, begin(mapping), bind(lower_bound<Array::iterator, int>, begin(mapping), end(mapping), placeholders::_1)));
}

inline
void derenumber(void)
{
    transform(&rectangle[0].left, &rectangle[rectangles].left, &rectangle[0].left,
        [&](int idx){return mapping[idx];});

    sort(rectangle, rectangle + rectangles);
}

inline
void solve(void)
{
    for(int r = 0; r < rectangles; ++ r)
        for(int t = 0; t < rectangles; ++ t)
            if(r != t && intersects(rectangle[r], rectangle[t]))
            {
                join(rectangle[r], rectangle[t]);
                rectangle[t].left = rectangle[t].right = rectangle[t].top = rectangle[t].bottom = -1000;
            }

    int t = 0;
    for(int r = 0; r < rectangles; ++ r)
    {
        if(rectangle[r].left < 0)
            continue;

        rectangle[t ++] = rectangle[r];
    }

    rectangles = t;
}

inline
bool intersects(const Rectangle &A, const Rectangle &B)
{
    return  A.left < B.right && A.right > B.left &&
            A.bottom < B.top && A.top > B.bottom;
}

inline
void join(Rectangle &dst, const Rectangle &src)
{
    dst.left    = min(dst.left,     src.left);
    dst.right   = max(dst.right,    src.right);
    dst.top     = max(dst.top,      src.top);
    dst.bottom  = min(dst.bottom,   src.bottom);
}

inline
bool Rectangle::operator<(const Rectangle &rect) const
{
    const int *a = &left;
    const int *b = &rect.left;
    for(int c = 0; c < 4; ++ a, ++ b, ++ c)
    {
        if(*a < *b)
            return true;

        if(*a > *b)
            return false;
    }

    return false;
}
