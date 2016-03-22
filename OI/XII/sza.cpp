/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<string>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

char buffer[524288];
int pi[524288],
	temp[1048576],
	rres[524288],
	rs,
	length,
	best;
bool flag;
std::string sWord;

inline static void findKMP(int *res, const std::string &word);

int main(void)
{
	scanf("%s%n", buffer, &length);
	sWord = buffer;
	findKMP(pi, sWord);
	best = length;
	while((length = pi[length - 1]))
		rres[rs ++] = length;

	while(rs --)
	{
		length = rres[rs];
		findKMP(temp, sWord.substr(0, length) + '#' + sWord);
		flag = true;
		for(int t = length + 1, l = length; flag && t < length + 1 + sWord.size(); ++ t)
		{
			if(temp[t] == length)
				l = t;

			flag = t - l < length;
		}

		if(flag)
		{
			best = length;
			break;
		}

		while(rs - 1 && length * 2 > rres[rs - 1])
			-- rs;
	}

	printf("%d\n", best);
	return 0;
}

inline static void findKMP(int *res, const std::string &word)
{
	for(unsigned int r = 0; r < word.size(); ++ r)
		res[r] = 0;

	for(unsigned int w = 1, j = 0; w < word.size(); ++ w)
	{
		while(j && word[w] != word[j])
			j = res[j - 1];

		if(word[w] == word[j])
			res[w] = ++ j;
	}

	return;
}
