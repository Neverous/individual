/*
 *
 * (C) Maciej Szeptuch 2007
 * Klocki - klo.cpp
 */
//Wczytywanie potrzebnych bibliotek ;)
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<vector>
#define SIZE 1048576 //Magiczna Liczba
#define INFTY 1000000000 // Jeszcze magiczniejsza ;P
#define suma second
#define ilosc first
using namespace std;
pair< int, long long unsigned int > blocks[SIZE*2]; //Magiczne drzewo ;)
long long unsigned int minChanges;	//Minimalna iloÅ›Ä‡ zmian
int amount,
    height;

vector< int > result; // wynik
/*-------------------------MAGICZNA STRUKTURA--------------------------------*/

bool insert(int i)	// Wrzucanie elementu do drzewa
{
	bool toReturn = true;
	int l = i+SIZE;
	if(blocks[l].ilosc != 0) toReturn = false;	//JeÅ›li juÅ¼ jest zwrÃ³Ä‡ FaÅ‚sz
	blocks[l].ilosc++;
	blocks[l].suma += i;
	for(int k = l;k>0;)	// przypisywanie odpowiednich wartoÅ›ci
	{
		k /= 2;
		blocks[k].suma += i;
		blocks[k].ilosc++;
	}
	return toReturn;
}

bool erase(int i)	//Usuwanie elementu z drzewa
{
	int l = i+SIZE;
	if(blocks[l].ilosc == 0) return false;	//JeÅ›li takiego nie ma zwrÃ³Ä‡ FaÅ‚sz
	blocks[l].suma -= i;
       	blocks[l].ilosc--;
	for(int k = l;k>0;)	// Odejmowanie odpowiednich wartoÅ›ci
	{
		k /= 2;
		blocks[k].suma -= i;
		blocks[k].ilosc--;
	}
	if(blocks[l].ilosc == 0) return true;	//JeÅ›li takiego nie ma zwrÃ³Ä‡ FaÅ‚sz
	return false;
}

int select(int i)	//Wybieranie i-tego elementu w drzewie
{
	int k = 1;
	if(blocks[1].ilosc<i)
		return -1;
	for(;k<SIZE;)
	{
		if(blocks[2*k].ilosc<i)
		{
			i -= blocks[2*k].ilosc;
			k = 2*k +1;
		}
		else
			k = 2*k;
	}
	return k - SIZE;
}

long long unsigned int selectAndSum(int i)
{
	int k = 1;
	if(blocks[1].ilosc<i)
		return -1;
	for(;k<SIZE;)
	{
		if(blocks[2*k].ilosc<i)
		{
			i -= blocks[2*k].ilosc;
			k = 2*k +1;
		}
		else
			k = 2*k;
	}
	long long unsigned int res = (blocks[k].suma/blocks[k].ilosc)*i;
	while(k>1)
	{
		if(k%2) res += blocks[k-1].suma;
		k/=2;
	}

	return res;
	
}
/*-------------------------------KONIEC STRUKTURY----------------------------*/

void solve(void)
{
	int i=0,
	    mediana=0,
	    elems=0,
	    position=0,
	    goodMediana=0;
	long long unsigned int sumK=0,
	     changes=0,
		 tmp=0;
	for(;i<height;i++)
	{
		if(insert(result[i]))
			elems++;
		sumK += result[i];
	}
	goodMediana = select(height/2 + height%2);
	tmp = selectAndSum(height/2 + height%2);
	minChanges = sumK - tmp*2+ goodMediana;
	if (!(height%2)) minChanges -= goodMediana;
	/*
	 * WYZNACZANIE LICZBY ZMIAN
	 */	
	for(;i<amount;i++)
	{
		sumK -= result[i-height];
		sumK += result[i];
		if(erase(result[i-height]))
			elems--;
		if(insert(result[i]))
			elems++;
		mediana = select(height/2 + height%2);
		tmp = selectAndSum(height/2 + height%2);
		changes = sumK - tmp*2 + mediana;
		if (!(height%2)) changes -= mediana;
		/*
		 * WYZNACZANIE LICZBY ZMIAN
		 */
		if(changes<minChanges)
		{
			position = 1+i-height;
			minChanges = changes;
			goodMediana = mediana;
		}
	}
	for(i=position;i<height+position;i++)
		result[i] = goodMediana;

}

/*---------------------------------------------------------------------------*/
int main(void)
{
	/* Wczytywanie danych */
	scanf("%d %d", &amount, &height);
	result.resize(amount);
	for(long int i=0;i<amount;i++)
		scanf("%d", &result[i]);
	
	/* RozwiÄ…zywanie */
	solve();
	printf("%llu\n", minChanges);
	for(long int i=0;i<amount;i++)
		printf("%d\n", result[i]);

	return 0;
}

