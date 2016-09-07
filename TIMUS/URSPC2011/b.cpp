/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>
#include<cmath>

long double ACCURACY = 1.0/1000000000000.0;

int first,
	second;
long double act,
			actres,
			result;

inline static const int MIN(const int &a, const int &b){return a<b?a:b;}
inline static const long double MAX(const long double &a, const long double &b){return a>b?a:b;}
inline static const long double ABS(const long double &a){return a>0?a:-a;}
inline static const long double func(const long double &x, const int &a, const int &b);
inline static const long double trinarySearch(long double start, long double end);

int main(void)
{
	scanf("%d %d", &first, &second);
	printf("%.10Lf\n", func(trinarySearch(0, MIN(first, second)), first, second));
	return 0;
}

inline static const long double func(const long double &x, const int &a, const int &b)
{
	return x * (2.0 * x + sqrt(a*a - x*x) + sqrt(b*b - x*x)) / 2.0;
}

inline static const long double trinarySearch(long double start, long double end)
{
	long double A, B,
				x, y;
	for(int m = 0; m < 4000000 && ABS(func(end, first, second) - func(start, first, second)) > ACCURACY; ++ m)
	{
		A = start + (end - start) / 3.0;
		B = start + (end - start) * 2.0 / 3.0;
		x = func(A, first, second);
		y = func(B, first, second);
		//printf("P: %.12Lf %.12Lf %.12Lf %.12Lf\n", start, A, B, end);
		if(x < y)
		{
			if(y < func(end, first, second))
				start = B;

			else
				start  = A;
		}

		else
		{
			if(func(start, first, second) > x)
				end = A;

			else
				end = B;
		}
	}

	return end;
}
