/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 * --------------
 *  Nadzieja na kilka poprawnościówek ^^
 */
#include<cstdio>
#include<cstdlib>
#include<set>
#define MODULO (long long int)1000007
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...) 

using namespace std;

struct Gcd
{
	long long int x,
				  y,
				  gcd;

	Gcd(long long int X = 0, long long int Y = 1, long long int G = 1)
	{
		x = X;
		y = Y;
		gcd = G;
	}
};

long long int factorial[1024],
			  width,
			  sum,
			  used,
			  tab[3][201];
bool zero,
	 fail;

void preprocess(void);
Gcd extGcd(long long int A, long long int B);
int easy(int number, int height);
int brute(int height, int iWidth);
int dfs(int h, int w, int maxH, int maxW, set<int> data);

int main(void)
{
	preprocess();
	scanf("%lld", &width);
	zero = false;
	fail = false;
	for(int h = 0; h < 3; ++ h)
		for(int w = 0; w < width; ++ w)
		{
			scanf("%lld", &tab[h][w]);
			if(!h && !w)
			{
				if(tab[h][w] && tab[h][w] != 1)
				{
					fail = true;
					break;
				}

				tab[h][w] = 0;
			}

			if(h == 2 && w == width - 1)
			{
				if(tab[h][w] && tab[h][w] != 3 * width)
				{
					fail = true;
					break;
				}

				tab[h][w] = 0;
			}
			zero = zero || tab[h][w];
			sum += tab[h][w];
		}

	if(fail)
	{
		printf("0\n");
		return 0;
	}

	if(!zero) // jak są same zera
	{
		printf("%d\n", easy(width, 3));
		return 0; // to chyba jest poprawne
	} 

	printf("%d\n", brute(3, width)); // to nie jest zbyt szybkie
	return 0;
}

void preprocess(void)
{
	factorial[1] = 1;
	for(long long int f = 2; f < 1024; ++ f)
		factorial[f] = (factorial[f - 1] * f) %  MODULO;

	return;
}

Gcd extGcd(long long int A, long long int B)
{
	Gcd res;
	long long int T;
	res.gcd = B;
	if(!B)
	{
		res.gcd = A;
		res.y = 0;
		res.x = 1;
		return res;
	}

	if(A % B == 0)
		return res;

	res = extGcd(B, A % B);
	T = res.x;
	res.x = res.y;
	res.y = T - res.y * (A / B);

	return res;
}

int easy(int number, int height)
{
	Gcd result,
		result2;
	long long int a,
				  b,
				  temp;
	a = (factorial[number * height] * (height - 1)) % MODULO;
	if(!a)
		a = factorial[number * height];

	b = 1;
	for(int h = 0; h < height; ++ h)
		b = (b * factorial[number + h]) % MODULO;

	result = extGcd(b, MODULO);
	if(result.x < 0)
	{
		temp = (result.x - result.y + 1)/result.y;
		result.x -= temp * MODULO;
		result.y += temp * b;
	}

	return (result.x * a) % MODULO;
}

int brute(int height, int iWidth)
{
	set<int> temp;
	for(int i = 1; i <= height * iWidth; ++ i)
		temp.insert(i);

	for(int h = 0; h < height; ++ h)
		for(int w = 0; w < iWidth; ++ w)
			if(tab[h][w])
			{
				temp.erase(tab[h][w]);
				++ used;
			}

	return dfs(0, 0, height, iWidth, temp);
}

int dfs(int h, int w, int maxH, int maxW, set<int> data)
{
	if(h == maxH - 1 && w == maxW - 1)
		return 1;

	if(tab[h][w])
	{
		data.erase(tab[h][w]);
		if(w + 1 < maxW)
			return dfs(h, w + 1, maxH, maxW, data);

		if(h + 1 < maxH)
			return dfs(h + 1, 0, maxH, maxW, data);

		return 0;
	}

	int result = 0;
	set<int> backup = data;
	set<int>::iterator start = data.lower_bound((h + 1) * (w + 1)),
					   end = data.upper_bound(maxH * maxW - (maxH - h) * (maxW - w) + 1);

	for(; start != data.end() && start != end; ++ start)
	{
		if(h && tab[h - 1][w] >= *start)
			continue;

		if(w && tab[h][w - 1] >= *start)
			continue;

		backup.erase(*start);
		tab[h][w] = *start;
		if(w + 1 < maxW)
			result += dfs(h, w + 1, maxH, maxW, backup);

		else if(h + 1 < maxH)
			result += dfs(h + 1, 0, maxH, maxW, backup);

		else
			break;

		result %= MODULO;

		backup.insert(*start);
		tab[h][w] = 0;
	}

	return result;
}
