/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...) 

int parts,
	part[65536],
	result,
	total,
	temp;

inline int MAX(const int &A, const int &B)
{
	return A > B?A:B;
}

inline int MIN(const int &A, const int &B)
{
	return A < B?A:B;
}

int main(void)
{
	scanf("%d", &parts);
	for(int p = 0; p < parts; ++ p)
	{
		scanf("%d", &part[p]);
		total += part[p];
	}

	/* BRUTE O(n^2) *//*
	for(int s = 0; s < parts; ++ s)
	{
		temp = part[s];
		for(int e = (s + 1) % parts; e != s; e = (e + 1) % parts)
		{
			result = MAX(result, MIN(temp, total - temp));
			temp += part[e];
		}
	}*/

	/* BEST O(n) */
	for(int s = 0, e = 0; s < parts && e < parts;)
	{
		if(temp + part[e] <= total / 2)
			temp += part[e ++];

		else
			temp -= part[s ++];

		result = MAX(result, temp);
	}
			
	printf("%d\n", result);
	return 0;
}

