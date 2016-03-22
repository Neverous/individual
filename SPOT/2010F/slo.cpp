/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<string>
#include<vector>
#include<algorithm>
#include<map>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

unsigned int tests,
			 gSeed,
			 translations,
			 fWord,
			 fLang,
			 tWord,
			 tLang,
			 reprCounter,
			 questions,
			 set,
			 unionTab[1 << 17];
bool done;
char fromWord[32],
	 fromLang[32],
	 toWord[32],
	 toLang[32];
std::map<unsigned int, std::map<unsigned int, unsigned int> > repr;
std::vector<std::pair<unsigned int, std::pair<unsigned int, std::string> > > dictionary;
std::vector<std::pair<unsigned int, std::pair<unsigned int, std::string> > >::iterator dict;

inline static unsigned int murmurHash(const void *key, int len, unsigned int seed);
inline static bool unionUnion(unsigned int a, unsigned int b);
inline static unsigned int unionFind(unsigned int a);

int main(void)
{
	srand(41);
	scanf("%u", &tests);
	for(unsigned int t = 0; t < tests; ++ t)
	{
		gSeed = rand() % (1 << 25);
		reprCounter = 1;
		dictionary.clear();
		repr.clear();
		for(unsigned int u = 0; u < (1 << 17); ++ u)
			unionTab[u] = u;

		scanf("%u", &translations);
		for(unsigned int tr = 0; tr < translations; ++ tr)
		{
			scanf("%s %s %s %s", fromWord, fromLang, toWord, toLang);
			fWord = murmurHash(fromWord, strlen(fromWord), gSeed);
			fLang = murmurHash(fromLang, strlen(fromLang), gSeed);
			tWord = murmurHash(toWord, strlen(toWord), gSeed);
			tLang = murmurHash(toLang, strlen(toLang), gSeed);
			if(!repr[tLang][tWord])
			{
				repr[tLang][tWord] = reprCounter ++;
				//printf("Adding: %u(%s) %u(%s) => %u\n", tLang, toLang, tWord, toWord, reprCounter - 1);
				dictionary.push_back(std::make_pair(reprCounter - 1, std::make_pair(tLang, std::string(toWord))));
			}

			if(!repr[fLang][fWord])
			{
				repr[fLang][fWord] = reprCounter ++;
				//printf("Adding: %u(%s) %u(%s) => %u\n", fLang, fromLang, fWord, fromWord, reprCounter - 1);
				dictionary.push_back(std::make_pair(reprCounter - 1, std::make_pair(fLang, std::string(fromWord))));
			}

			unionUnion(repr[tLang][tWord], repr[fLang][fWord]);
		}

		//for(unsigned int d = 0; d < dictionary.size(); ++ d)
		//printf("%u %u %s\n", dictionary[d].first, dictionary[d].second.first, dictionary[d].second.second.c_str());

		for(unsigned int d = 0; d < dictionary.size(); ++ d)
			dictionary[d].first = unionFind(dictionary[d].first);

		//puts("");
		std::sort(dictionary.begin(), dictionary.end());
		//for(unsigned int d = 0; d < dictionary.size(); ++ d)
		//printf("%u %u %s\n", dictionary[d].first, dictionary[d].second.first, dictionary[d].second.second.c_str());

		scanf("%u", &questions);
		for(unsigned int q = 0; q < questions; ++ q)
		{
			scanf("%s %s %s", fromWord, fromLang, toLang);
			fWord = murmurHash(fromWord, strlen(fromWord), gSeed);
			fLang = murmurHash(fromLang, strlen(fromLang), gSeed);
			tLang = murmurHash(toLang, strlen(toLang), gSeed);
			set = unionFind(repr[fLang][fWord]);
			dict = lower_bound(dictionary.begin(), dictionary.end(), std::make_pair(set, std::make_pair(tLang, std::string())));
			//printf("Looking for: %u(%s) %u(%s) => %u %u\n", fLang, fromLang, fWord, fromWord, set, tLang);
			done = false;
			while(dict != dictionary.end() && dict->first == set && dict->second.first == tLang)
			{
				if(done)
					putchar(',');

				printf("%s", dict->second.second.c_str());
				done = true;
				++ dict;
			}

			if(!done)
				printf("?");

			puts("");
		}
	}

	return 0;
}

inline static unsigned int murmurHash(const void *key, int len, unsigned int seed)
{
	const unsigned int m = 0x5bd1e995;
	const int r = 24;
	unsigned int h = seed ^ len;
	const unsigned char * data = (const unsigned char *)key;
	while(len >= 4)
	{
		unsigned int k = *(unsigned int *)data;
		k *= m;
		k ^= k >> r;
		k *= m;
		h *= m;
		h ^= k;
		data += 4;
		len -= 4;
	}

	switch(len)
	{
		case 3: h ^= data[2] << 16;
		case 2: h ^= data[1] << 8;
		case 1: h ^= data[0];
				h *= m;
	};

	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;
	return h;
}

inline static unsigned int unionFind(unsigned int a)
{
	if(unionTab[a] != a)
		unionTab[a] = unionFind(unionTab[a]);

	return unionTab[a];
}

inline static bool unionUnion(unsigned int a, unsigned int b)
{
	unsigned int fA = unionFind(a),
				 fB = unionFind(b);

	if(fA == fB)
		return false;

	if(fA < fB)
		unionTab[fB] = fA;

	else
		unionTab[fA] = fB;

	return true;
}
