/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<algorithm>

class Spiece
{
	public:
		int length,
			weight,
			segments,
			spiece;

		inline const bool operator<(const Spiece &B) const;
};

int tests,
	spieces,
	dLength, dWeight, dSegments,
	count,
	result[80008];
Spiece spiece[80008];

inline static const int ABS(const int &a){return a<0?-a:a;}

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d", &spieces);
		scanf("%d %d %d", &dLength, &dWeight, &dSegments);
		for(int s = 0; s < spieces; ++ s)
		{
			scanf("%d %d %d", &spiece[s].length, &spiece[s].weight, &spiece[s].segments);
			spiece[s].spiece = s;
		}

		std::sort(spiece, spiece + spieces);

		for(int s = 0, i = 0, j = 0; s < spieces; ++ s)
		{
			count = 0;
			while(spiece[i].length < spiece[s].length - dLength)
				++ i;

			while(j < spieces && spiece[s].length + dLength >= spiece[j].length)
				++ j;

			for(int p = i; p < j; ++ p)
				count += ABS(spiece[s].weight - spiece[p].weight) <= dWeight &&
				   ABS(spiece[s].segments - spiece[p].segments) <= dSegments;

			result[spiece[s].spiece] = count - 1;
		}

		for(int s = 0; s < spieces; ++ s)
			printf("%d ", result[s]);

		puts("");
	}

	return 0;
}

inline const bool Spiece::operator<(const Spiece &B) const
{
	if(this->length < B.length)
		return true;

	if(this->length > B.length)
		return false;

	if(this->weight < B.weight)
		return true;

	if(this->weight > B.weight)
		return false;

	return this->segments < B.segments;
}
