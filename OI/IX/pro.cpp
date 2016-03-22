/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 * ----------
 *  BIGNUMY!!!!!
 */
#include<cstdio>
#include<cmath>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int values,
	frequency,
	packageSize,
	change;

int validPackages(int size);

int main(void)
{
	scanf("%d %d %d %d", &values, &frequency, &packageSize, &change);
	printf("%d\n", (int)(frequency * log2(validPackages(packageSize)) / packageSize));
	return 0;
}

int validPackages(int size)
{
	if(!size)
		return 1;

	if(size <= change)
		return values * validPackages(size - 1) - (size == change) * values;

	return values * validPackages(size - 1) - (values - 1) * validPackages(size - change);
}
