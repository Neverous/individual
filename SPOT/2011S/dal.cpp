/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<algorithm>

int tests,
	size,
	height,
	shots,
	burn[3];

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d", &size);
		shots = 0;
		burn[0] = burn[1] = burn[2];
		for(int s = 0; s < size; ++ s)
		{
			scanf("%d", &height);
			while(height && burn[0])
			{
				height /= 2;
				-- burn[0];
			}

			while(height)
			{
				++ shots;
				++ burn[1];
				++ burn[2];
				height /= 2;
			}

			std::swap(burn[0], burn[1]);
			std::swap(burn[1], burn[2]);
			burn[2] = 0;
		}

		printf("%d\n", shots);
	}

	return 0;
}

