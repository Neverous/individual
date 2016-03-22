/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>
#include<cstring>

int tests,
	size,
	window,
	paint[808][808],
	revpaint[800][808],
	result[808][808],
	count[1048576],
	colors;

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %d", &size, &window);
		colors = 0;
		bzero(count, sizeof(count));
		for(int h = 0; h < size; ++ h)
			for(int w = 0; w < size; ++ w)
			{
				scanf("%d", &paint[h][w]);
				revpaint[w][h] = paint[h][w];
			}

		/* FIRST WINDOW */
		for(int h = 0; h < window; ++ h)
			for(int w = 0, *p = paint[h]; w < window; ++ w)
			{
				if(!count[p[w]])
					++ colors;

				++ count[p[w]];
			}

		result[0][0] = colors;
		/* MOVING WINDOW */
		for(int h = 0, p = 1, end = size - window, ps = p?0:size - window; h <= end; ++ h, p = !p, ps = p?0:size - window)
		{
			/* MOVE UP */
			if(h)
			{
				for(int l = 0, *a = paint[h - 1], *b = paint[h + window - 1]; l < window; ++ l)
				{
					-- count[a[ps + l]];
					if(!count[a[ps + l]])
						-- colors;

					if(!count[b[ps + l]])
						++ colors;

					++ count[b[ps + l]];
				}

				result[h][ps] = colors;
			}

			/* MOVE HORIZONTALLY */
			if(p) // MOVE RIGHT
			{
				for(int w = 1, *r = result[h]; w <= end; ++ w)
				{
					for(int l = 0, *a = revpaint[w - 1], *b = revpaint[w + window - 1]; l < window; ++ l)
					{
						-- count[a[h + l]];
						if(!count[a[h + l]])
							-- colors;

						if(!count[b[h + l]])
							++ colors;

						++ count[b[h + l]];
					}

					r[w] = colors;
				}
			}
			else // MOVE LEFT
			{
				for(int w = end - 1, *r = result[h]; w >= 0; -- w)
				{
					for(int l = 0, *a = revpaint[w + window], *b = revpaint[w]; l < window; ++ l)
					{
						-- count[a[h + l]];
						if(!count[a[h + l]])
							-- colors;

						if(!count[b[h + l]])
							++ colors;

						++ count[b[h + l]];
					}

					r[w] = colors;
				}
			}
		}

		/* PRINTING RESULT */
		for(int h = 0, end = size - window; h <= end; ++ h)
			for(int w = 0, *r = result[h]; w <= end; ++ w)
				printf("%d%c", r[w], w == end?'\n':' ');
	}

	return 0;
}

