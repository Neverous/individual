/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<algorithm>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

long long find;
//int memorize[4000000];
long long numbers[68] = {
	1LL,
	2LL,
	4LL,
	6LL,
	12LL,
	24LL,
	36LL,
	48LL,
	60LL,
	120LL,
	180LL,
	240LL,
	360LL,
	720LL,
	840LL,
	1260LL,
	1680LL,
	2520LL,
	5040LL,
	7560LL,
	10080LL,
	15120LL,
	20160LL,
	25200LL,
	27720LL,
	45360LL,
	50400LL,
	55440LL,
	83160LL,
	110880LL,
	166320LL,
	221760LL,
	277200LL,
	332640LL,
	498960LL,
	554400LL,
	665280LL,
	720720LL,
	1081080LL,
	1441440LL,
	2162160LL,
	2882880LL,
	3603600LL,
	4324320LL,
	6486480LL,
	7207200LL,
	8648640LL,
	10810800LL,
	14414400LL,
	17297280LL,
	21621600LL,
	32432400LL,
	36756720LL,
	43243200LL,
	61261200LL,
	73513440LL,
	110270160LL,
	122522400LL,
	147026880LL,
	183783600LL,
	245044800LL,
	294053760LL,
	367567200LL,
	551350800LL,
	698377680LL,
	735134400LL,
	1102701600LL,
	1396755360LL,
};

//void prepare(void);
long long best(long long &number);

int main(void)
{
	//	prepare();
	scanf("%lld", &find);
	printf("%lld\n", best(find));
	return 0;
}

/*
   void prepare(void)
   {
   for(int m = 0; m < 4000000; ++ m)
   memorize[m] = 0;

   printf("int numbers[] = {\n");
   int biggest = 0;
   for(int n = 1, number = 1, r = 1; n < 2000000000; number = ++ n, r = 1)
   {
   for(int p = 2, c = 0; p * p <= number && (number > 4000000 || !memorize[number]) ; ++ p, c = 0)
   {
   while(number % p == 0)
   {
   ++ c;
   number /= p;
   }

   r *= c + 1;
   }

   if(number < 4000000 && memorize[number])
   r *= memorize[number];

   else if(number != 1)
   r *= 2;

   if(n < 4000000)
   memorize[n] = r;

   if(r > biggest)
   {
   printf("\t%d,\n", n);
   biggest = r;
   }
   }

   printf("\t};\n");
   throw;
   }
   */

long long best(long long &number)
{
	long long *result = std::lower_bound(numbers, numbers + 67, number);
	if(*result > number)
		-- result;

	return *result;

}
