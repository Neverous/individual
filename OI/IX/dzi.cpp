/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...) 

int size,
	tmp,
	col[2048],
	result;

int processRow(int *tab, int &width);

int main(void)
{
	scanf("%d", &size);
	for(int h = 0; h < size; ++ h)
	{
		for(int w = 1; w <= size; ++ w)
		{
			scanf("%d", &tmp);
			if(tmp)
				col[w] = 0;

			else
				++ col[w];
		}

		tmp = processRow(col, size);
		result = tmp > result?tmp:result;
	}

	printf("%d\n", result);
	return 0;
}

int processRow(int *tab, int &width)
{
	int stack[2048],
		right[2048],
		left[2048],
		s = 0,
		res = 0;

	/* RIGHT */
	tab[width + 1] = -1;
	for(int w = 0; w <= width + 1; ++ w)
	{
		while(s && tab[stack[s - 1]] > tab[w])
		{
			right[stack[s - 1]] = w;
			-- s;
		}

		stack[s ++] = w;
	}

	/* LEFT */
	for(int w = width + 1; w >= 0; -- w)
	{
		while(s && tab[stack[s - 1]] > tab[w])
		{
			left[stack[s - 1]] = w;
			-- s;
		}

		stack[s ++] = w;
	}

	for(int w = 1; w <= width; ++ w)
		res = res < (right[w] - left[w] - 1) * tab[w]?(right[w] - left[w] - 1) * tab[w]:res;

	return res;
}

