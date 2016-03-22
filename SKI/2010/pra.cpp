/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<algorithm>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int firstLength,
	secondLength,
	zeros,
	ones,
	zerosF,
	zerosS,
	onesF,
	onesS,
	maxLength,
	lastOne,
	lastZero;
std::pair<int, int> result[100010];
char first[100010],
	 second[100010];

int main(void)
{
	scanf("%d %d %s %s", &firstLength, &secondLength, first, second);
	for(int f = 0; f < firstLength; ++ f)
	{
		if(first[f] == '0')
			++ zerosF;

		else
			++ onesF;
	}

	for(int s = 0; s < secondLength; ++ s)
	{
		if(second[s] == '0')
			++ zerosS;

		else
			++ onesS;
	}

	maxLength = firstLength < secondLength?firstLength:secondLength;
	zeros = zerosS < zerosF?zerosS:zerosF;
	ones = onesS < onesF?onesS:onesF;
	if(zeros * 2 > maxLength)
	{
		printf("%d\n", zeros);
		for(int c = 0; c < zeros; ++ c)
			putchar('0');

		puts("");
		return 0;
	}

	if(ones * 2 > maxLength)
	{
		printf("%d\n", ones);
		for(int c = 0; c < ones; ++ c)
			putchar('1');

		puts("");
		return 0;
	}

	/* DP START */
	if(secondLength < firstLength)
	{
		for(int a = 0; a < 100010; ++ a)
			std::swap(first[a], second[a]);

		std::swap(secondLength, firstLength);
	}

	lastOne = 0;
	lastZero = 0;
	result[0].second = -1;
	for(int f = 0, pos; f < firstLength; ++ f)
	{
		result[f + 1] = result[f];
		if(first[f] == '0') // LOOKING FOR ZERO
		{
			//printf("SZUKAM 0\n");
			pos = result[lastZero].second;
			//printf(">>%d\n", pos);
			for(int r = lastZero; r < f + 1; ++ r)
			{
				while(pos < secondLength && (second[pos] != '0' || pos <= result[r].second))
					//{
					//printf("X> %c %d\n", second[pos], pos);
					++ pos;
				//}

				//printf("%d %d\n", r, pos);
				if(pos < secondLength && second[pos] == '0' && result[f + 1].first < result[r].first + 1)
					result[f + 1] = std::make_pair(result[r].first + 1, pos);

			}

			lastZero = f + 1;
		}

		else // LOOKING FOR ONE
		{
			//printf("SZUKAM 1\n");
			pos = result[lastOne].second;
			//printf(">>%d\n", pos);
			for(int r = lastOne; r < f + 1; ++ r)
			{
				while(pos < secondLength && (second[pos] != '1' || pos <= result[r].second))
				{
					printf("X> %c %d %d\n", second[pos], pos, result[r].second);
					++ pos;
				}

				printf("%d %d\n", r, pos);
				if(pos < secondLength && second[pos] == '1' && result[f + 1].first <= result[r].first + 1)
					result[f + 1] = std::make_pair(result[r].first + 1, pos);

			}

			lastOne = f + 1;
		}
	}

	for(int f = 0; f <= firstLength; ++ f)
		printf("%d ", result[f].first);

	puts("");
	for(int f = 0; f <= firstLength; ++ f)
		printf("%d ", result[f].second);

	puts("");

	if(result[firstLength].first <= ones && result[firstLength].first >= zeros)
	{
		printf("%d\n", ones);
		for(int c = 0; c < ones; ++ c)
			putchar('1');

		puts("");
		return 0;
	}

	if(result[firstLength].first >= ones && result[firstLength].first <= zeros)
	{
		printf("%d\n", zeros);
		for(int c = 0; c < zeros; ++ c)
			putchar('0');

		puts("");
		return 0;
	}

	printf("%u\n", result[firstLength].first);
	second[result[firstLength].first] = 0;
	for(int p = firstLength; p > 0 && result[p].first; -- p)
	{
		if(result[p].first == result[p -  1].first)
			continue;

		second[-- result[firstLength].first] = first[p - 1];
	}

	printf("%s\n", second);
	return 0;
}
