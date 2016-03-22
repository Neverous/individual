/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <algorithm>

int height, width,
    maxWidth = 2536, maxHeight = 2536,
    stencilWidth = 1, stencilHeight = 1,
    best[2536],
    down[2536][2536],
    up[2536][2536];
char row[2536][2536];

int main(void)
{
    scanf("%d %d", &height, &width);
    for(int h = 1; h <= height; ++ h)
        scanf("%s", row[h] + 1);

    /* count max stencil width */
    for(int h = 1; h <= height; ++ h)
        for(int w = 1, cnt = 0; w <= width + 1; ++ w)
        {
            if(row[h][w] != 'X')
            {
                if(cnt)
                {
                    maxWidth = std::min(maxWidth, cnt);
                    cnt = 0;
                }

                continue;
            }

            ++ cnt;
        }

    /* count max stencil height */
    for(int w = 1; w <= width; ++ w)
        for(int h = 1, cnt = 0; h <= height + 1; ++ h)
        {
            if(row[h][w] != 'X')
            {
                if(cnt)
                {
                    maxHeight = std::min(maxHeight, cnt);
                    cnt = 0;
                }

                continue;
            }

            ++ cnt;
        }

    for(int w = 0; w < 2536; ++ w)
        best[w] = maxHeight;

    /* count max down heights */
    for(int w = 1; w <= width; ++ w)
        for(int h = height; h > 0; -- h)
            if(row[h][w] == 'X')
                down[h][w] = down[h + 1][w] + 1;

    /* count max up heights */
    for(int w = 1; w <= width; ++ w)
        for(int h = 1; h <= height; ++ h)
            if(row[h][w] == 'X')
                up[h][w] = up[h - 1][w] + 1;

    /* count real size */
    for(int h = 1; h <= height; ++ h)
        for(int w = 1, c = 1, _up = up[h][w], _down = down[h][w]; w <= width; ++ w, ++ c)
        {
            if(row[h][w] != 'X')
            {
                c = 0;
                _up = 2536;
                _down = 2536;
                continue;
            }

            _up = std::min(_up, up[h][w]);
            _down = std::min(_down, down[h][w]);
            best[c] = std::min(best[c], _up + _down - 1);
        }

    for(int h = 1; h <= height; ++ h)
        for(int w = width, c = 1, _up = up[h][w], _down = down[h][w]; w > 0; -- w, ++ c)
        {
            if(row[h][w] != 'X')
            {
                c = 0;
                _up = 2536;
                _down = 2536;
                continue;
            }

            _up = std::min(_up, up[h][w]);
            _down = std::min(_down, down[h][w]);
            best[c] = std::min(best[c], _up + _down - 1);
        }


    for(int w = 1; w <= maxWidth; ++ w)
        if(best[w] * w >= stencilHeight * stencilWidth)
        {
            stencilHeight = best[w];
            stencilWidth = w;
        }

    printf("%d %d\n", stencilHeight, stencilWidth);

    return 0;
}
