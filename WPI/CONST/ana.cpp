/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<algorithm>
#include<string>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...) 

using namespace std;

char buffer[32],
	 sortedBuffer[32];
pair<int, pair<string, string> > data[100001];
pair<string, int> smallest[100001];
int words,
	counts,
	bestCount,
	twoElements,
	length,
	quant[100001],
	ssize;

int main(void)
{
	while(scanf("%s", buffer) != -1 && buffer[0] != '0')
	{
		for(length = 0; buffer[length]; ++ length)
			sortedBuffer[length] = buffer[length];

		sortedBuffer[length] = 0;
		sort(sortedBuffer, sortedBuffer + length);
		data[words ++] = make_pair(length, make_pair(string(sortedBuffer), string(buffer)));
	}

	sort(data, data + words);
	quant[0] = 1;
	for(int w = 0; w < words; ++ w)
	{
		if(w && data[w - 1].first == data[w].first &&
			data[w - 1].second.first == data[w].second.first)
			++ counts;

		else
		{
			if(counts > 1)
				smallest[ssize ++] = make_pair(data[w - counts].second.second, w - counts);

			quant[w - counts] = counts;
			bestCount = bestCount < counts?counts:bestCount;
			twoElements += counts > 1;
			counts = 1;
		}
	}

	bestCount = bestCount < counts?counts:bestCount;
	twoElements += counts > 1;
	quant[words - counts] = counts;
	if(counts > 1)
		smallest[ssize ++] = make_pair(data[words - counts].second.second, words - counts);

	printf("%d\n", twoElements);
	if(!twoElements)
		return 0;

	sort(smallest, smallest + ssize);
	printf("%d\n", bestCount);
	for(int s = 0; s < ssize; ++ s)
	{
		if(quant[smallest[s].second] != bestCount)
			continue;

		for(int w = smallest[s].second, act = 0; act < quant[smallest[s].second]; ++ act, ++ w)
			printf("%s ", data[w].second.second.c_str());

		puts("");
	}

	return 0;
}

