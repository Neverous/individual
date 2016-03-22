/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>

int length,
	act,
	min,
	b,
	result,
	f, s, p;
char word[1048576],
	 alphabet[32],
	 alph;
bool lastb;

inline static int MIN(const int &a, const int &b){return a<b?a:b;}

int main(void)
{
	scanf("%d %s", &length, word + 1);
	for(int w = 1; w <= length; ++ w)
	{
		if(!alphabet[word[w] -= 'a'])
			alphabet[word[w]] = ++ alph;
	}

	/* N */
	for(f = 1; f <= alph; ++ f)
		for(s = 1; s <= alph; ++ s)
			for(p = 1, act = min = b = lastb = false; p <= length; ++ p)
			{
				if(alphabet[word[p]] == f)
					++ act;

				if(alphabet[word[p]] == s)
				{
					min = MIN(b, min);
					lastb = true;
					b = -- act;
				}

				if(lastb && result < act - min)
					result = act - min;
			}

	printf("%d\n", result);
	return 0;
}

