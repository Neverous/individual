/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>

int tests,
	latitude,
	height,
	width,
	flag,
	map[303][303],
	visited[303][303];
bool dontstart[303][303];

int solve(void);
int dfs(int h, int w, int starts);

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %d %d", &latitude, &height, &width);
		for(int h = 1; h <= height; ++ h)
			for(int w = 1; w <= width; ++ w)
			{
				scanf("%d", &map[h][w]);
				map[h][w] += 100;
				map[h + 1][w] = map[h][w + 1] = map[h + 1][w + 1] = 0;
				visited[h][w] = 0;
				dontstart[h][w] = false;
			}

		flag = 1;
		printf("%d\n", solve());
	}

	return 0;
}

int solve(void)
{
	int max = 1,
		tmp = 0;

	for(int h = 1; h <= height; ++ h)
		for(int w = 1; w <= width; ++ w)
			if(!dontstart[h][w])
			{
				tmp = dfs(h, w, map[h][w]);
				if(tmp > max)
					max = tmp;

				++ flag;
			}

	return max;
}

int dfs(int h, int w, int starts)
{
	if(visited[h][w] == flag)
		return 0;

	visited[h][w] = flag;
	if(map[h][w] == starts)
		dontstart[h][w] = true;
	
	int count = 1;
	for(int i = -1; i < 2; ++ i)
	{
		if(i == 0)
			continue;

		if(starts <= map[h + i][w] && map[h + i][w] - starts <= latitude)
			count += dfs(h + i, w, starts);

		if(starts <= map[h][w + i] && map[h][w + i] - starts <= latitude)
			count += dfs(h, w + i, starts);
	}

	return count;
}
