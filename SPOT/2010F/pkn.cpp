/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

unsigned int tests;
long double Ap, Ak, An,
			Gp, Gk, Gn,
			G, A;

int main(void)
{
	scanf("%u", &tests);
	for(unsigned int t = 0; t < tests; ++ t)
	{
		scanf("%Lf %Lf %Lf", &Ap, &Ak, &An);
		scanf("%Lf %Lf %Lf", &Gp, &Gk, &Gn);

		G = Gp * Ak + Gk * An + Gn * Ap;
		A = Ap * Gk + Ak * Gn + An * Gp;
		if(G > A)
			printf("GOSIA\n");

		else if(A > G)
			printf("ADAM\n");

		else
			printf("=\n");
	}
	return 0;
}

