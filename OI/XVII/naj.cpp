/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 * --------------
 *  To nadal jest strasznie brzydki kod...
 */
#include<cstdio>
#include<cstdlib>
#include<set>
#include<vector>
#include<cstring>
#include<cmath>
#define DUZO 1000000000LLU

using namespace std;

struct BigNum
{
	long long unsigned int repr[30];
	BigNum(long long unsigned int number = 0)
	{
		memset(repr, 0, sizeof(long long unsigned int) * 30);
		repr[29] = number % DUZO;
		repr[28] = number / DUZO;
		return;
	}

	inline BigNum operator*(const BigNum A) const
	{
		BigNum R;
		int p = 0;
		for(int r = 29; r >= 0; -- r)
			for(int r1 = 29; r1 >= 0; -- r1)
			{
				p = r + r1 - 29;
				if(p < 0)
					break;

				R.repr[p] += repr[r] * A.repr[r1];
				if(p)
					R.repr[p - 1] += R.repr[p] / DUZO;

				R.repr[p] %= DUZO;
			}

		return R;
	}

	inline BigNum operator*(const long long unsigned int A) const
	{
		BigNum R = *this;
		for(int r = 29; r >= 0; -- r)
		{
			R.repr[r] *= A;
			if(r)
				R.repr[r - 1] += R.repr[r] / DUZO;

			R.repr[r] %= DUZO;
		}

		return R;
	}

	inline BigNum operator-(const long long unsigned int A) const
	{
		BigNum R = *this;
		int r = 0;
		if(A > R.repr[29])
		{
			for(r = 28; r >= 0 && !R.repr[r]; -- r)
				R.repr[r] += 999999999;

			if(r > 0)
				R.repr[r] -= 1;

			R.repr[29] += 1000000000;
		}

		R.repr[29] -= A;

		return R;
	}

	inline void print(void) const
	{
		bool printing = false;

		for(int r = 0; r < 30; ++ r)
		{
			if(printing)
				printf("%09llu", repr[r]);

			else if(repr[r] > 0)
			{
				printing = true;
				printf("%llu", repr[r]);
			}
		}

		if(!printing)
			printf("0");

		puts("");

		return;
	}
};// BigNumy...

inline void solve(void);

inline void preprocess(void);
inline void process(long long unsigned int check);
inline void factorizeEratostenes(long long unsigned int &num, long long unsigned int &divisor);
inline void factorizeBrute(long long unsigned int &num, long long unsigned int &d);
inline void factorizeShanks(long long unsigned int &num);
inline long long unsigned int gcd(long long unsigned int A, long long unsigned int B);
inline bool checkPrime(long long unsigned int &num);

long long unsigned int fastPower(long long unsigned int a, long long unsigned int power, long long unsigned int MODULO);
inline long long unsigned int multiply(long long unsigned int A, long long unsigned int B, long long unsigned int MOUDLO);
BigNum fastPower(BigNum A, int power);

set<pair<long long unsigned int, unsigned short int> > result;
set<pair<unsigned short int, long long unsigned int> > best;
set<pair<long long unsigned int, unsigned short int> >::iterator pos;
int numbers,
	res;
long long unsigned int number,
					   number2;
bool isPrime[1000010];
vector<unsigned int> primes;

int main(void)
{
	preprocess();
	scanf("%d", &numbers);
	for(int n = 0; n < numbers; ++ n)
	{
		scanf("%llu", &number);
		process(number);
	}

	solve();
	return 0;
}

inline void process(long long unsigned int check)
{
	if(check == 1)
		return;

	long long unsigned int divisor = 0;
	pos = result.lower_bound(pair<long long unsigned int, unsigned short int>(check, 0));
	if((pos != result.end() && pos->first == check) || checkPrime(check))
	{
		res = 1;
		if(pos != result.end() && pos->first == check)
		{
			res += pos->second;
			result.erase(pos);
			best.erase(pair<unsigned short int, long long unsigned int>(pos->second, pos->first));
		}

		result.insert(pair<long long unsigned int, unsigned short int>(check, res));
		best.insert(pair<unsigned short int, long long unsigned int>(res, check));
		check = 1;

		return;
	} // Jest liczba pierwsza

	factorizeEratostenes(check, divisor);
	//factorizeShanks(check); - tylko spowalnia... ;/
	factorizeBrute(check, divisor);
	return;
}

inline void solve(void)
{
	if(best.empty())
	{
		printf("1\n1\n");
		return;
	}

	unsigned int many = distance(best.lower_bound(pair<unsigned short int, long long unsigned int>(best.rbegin()->first, 0)), best.end());
	unsigned short int power = best.rbegin()->first;

	printf("%u\n", power);
	(fastPower(BigNum(2), many) - 1).print();
}

void preprocess(void)
{
	for(int p = 0; p <= 1000000; ++ p)
		isPrime[p] = true;

	for(int p = 2; p <= 1000000; ++ p)
	{
		if(!isPrime[p])
			continue;

		primes.push_back(p);
		for(long long int j = (long long int)p * p; j <= 1000000; j += p)
			isPrime[j] = false;	
	}
}

inline bool checkPrime(long long unsigned int &num)
{
	if(num == 2)
		return true;

	if(num % 2 == 0)
		return false;

	for(unsigned int p = 0; p < 32 && primes[p] < num; ++ p)
		if(num % primes[p] == 0 || fastPower(primes[p], num - 1, num) != 1)
			return false;

	return true;
}

long long unsigned int fastPower(long long unsigned int a, long long unsigned int power, long long unsigned int MODULO)
{
	if(power == 0)
		return 1;

	if(power % 2)
		return multiply(a, fastPower(a, power - 1, MODULO), MODULO);

	long long unsigned int half = fastPower(a, power / 2, MODULO);
	return multiply(half, half, MODULO);
}

inline long long unsigned int multiply(long long unsigned int A, long long unsigned int B, long long unsigned int MODULO)
{
	long long unsigned int a = A,b = B;
	int len = 0;
	while(a)
	{
		a /= 10;
		++ len;
	}

	while(b)
	{
		b /= 10;
		++ len;
	}

	if(len < 19)
		return (A*B) % MODULO;

	if(A < B)
		swap(A, B);

	long long unsigned int A2 = A / DUZO,
		 A1 = A % DUZO,
		 B2 = B / DUZO,
		 B1 = B % DUZO,
		 R4 = 0,
		 R3 = 0,
		 R2 = 0,
		 R1 = 0,
		 pow = 1;

	R1 = A1 * B1;
	R2 += R1 / DUZO;
	R1 %= DUZO;

	R2 += A1 * B2 + A2 * B1;
	R3 += R2 / DUZO;
	R2 %= DUZO;

	R3 += A2 * B2;
	R4 += R3 / DUZO;
	R3 %= DUZO;

	if(R4)
		pow = DUZO / 10;

	else
		while(pow <= R3 / 10)
			pow *= 10;

	for(; pow > 0; pow /= 10)
	{
		R4 = R4 * 10 + (R3 / pow) % 10;
		R4 %= MODULO;
	}

	pow = 1;
	if(R3)
		pow = DUZO / 10;

	else
		while(pow <= R2 / 10)
			pow *= 10;

	for(; pow > 0; pow /= 10)
	{
		R4 = R4 * 10 + (R2 / pow) % 10;
		R4 %= MODULO;
	}

	pow = 1;
	if(R2)
		pow = DUZO / 10;

	else
		while(pow <= R1 / 10)
			pow *= 10;

	for(; pow > 0; pow /= 10)
	{
		R4 = R4 * 10 + (R1 / pow) % 10;
		R4 %= MODULO;
	}

	return R4;
}

BigNum fastPower(BigNum A, int power)
{
	if(power == 0)
		return 1;

	if(power % 2)
		return A * fastPower(A, power - 1);

	BigNum half = fastPower(A, power / 2);
	return half * half;
}

inline void factorizeEratostenes(long long unsigned int &num, long long unsigned int &divisor)
{
	if(num == 1)
		return;

	for(unsigned int p = 0; p < primes.size() && num > 1 && (long long unsigned int)primes[p] * primes[p] <= num; ++ p)
	{
		divisor = primes[p];
		if(num % primes[p] == 0)
		{
			res = 0;
			while(num % primes[p] == 0)
			{
				++ res;
				num /= primes[p];
			}

			pos = result.lower_bound(pair<long long unsigned int, unsigned short int>(primes[p], 0));
			if(pos != result.end() && pos->first == primes[p])
			{
				res += pos->second;
				result.erase(pos);
				best.erase(pair<unsigned short int, long long unsigned int>(pos->second, pos->first));
			}

			result.insert(pair<long long unsigned int, unsigned short int>(primes[p], res));
			best.insert(pair<unsigned short int, long long unsigned int>(res, primes[p]));
		}

		pos = result.lower_bound(pair<long long unsigned int, unsigned short int>(num, 0));
		if(num > 1 && pos != result.end() && pos->first == num)
		{
			res = 1;
			if(pos != result.end() && pos->first == num)
			{
				res += pos->second;
				result.erase(pos);
				best.erase(pair<unsigned short int, long long unsigned int>(pos->second, pos->first));
			}

			result.insert(pair<long long unsigned int, unsigned short int>(num, res));
			best.insert(pair<unsigned short int, long long unsigned int>(res, num));
			num = 1;

			return;
		} // Jest liczba pierwsza
	}

	if(num > 1 && num < (long long unsigned int)1000000000000LLU)
	{
		res = 1;
		pos = result.lower_bound(pair<long long unsigned int, unsigned short int>(num, 0));
		if(pos != result.end() && pos->first == num)
		{
			res += pos->second;
			result.erase(pos);
			best.erase(pair<unsigned short int, long long unsigned int>(pos->second, pos->first));
		}

		result.insert(pair<long long unsigned int, unsigned short int>(num, res));
		best.insert(pair<unsigned short int, long long unsigned int>(res, num));
		num = 1;

		return;
	} // Jest liczba pierwsza
}

inline void factorizeBrute(long long unsigned int &num, long long unsigned int &d)
{
	long long unsigned int last = 0;
	char k = 2;
	while((long long unsigned int)d * d <= num)
	{
		if(num % d == 0)
		{
			res = 0;
			while(num % d == 0)
			{
				++ res;
				num /= d;
			}

			pos = result.lower_bound(pair<long long unsigned int, unsigned short int>(d, 0));
			if(pos != result.end() && pos->first == d)
			{
				res += pos->second;
				result.erase(pos);
				best.erase(pair<unsigned short int, long long unsigned int>(pos->second, pos->first));
			}

			result.insert(pair<long long unsigned int, unsigned short int>(d, res));
			best.insert(pair<unsigned short int, long long unsigned int>(res, d));
		}

		if(last != num)
		{
			pos = result.lower_bound(pair<long long unsigned int, unsigned short int>(num, 0));
			if(num > 1 && ((pos != result.end() && pos->first == num) || checkPrime(num)))
			{
				res = 1;
				if(pos != result.end() && pos->first == num)
				{
					res += pos->second;
					result.erase(pos);
					best.erase(pair<unsigned short int, long long unsigned int>(pos->second, pos->first));
				}

				result.insert(pair<long long unsigned int, unsigned short int>(num, res));
				best.insert(pair<unsigned short int, long long unsigned int>(res, num));
				num = 1;

				return;
			} // Jest liczba pierwsza
		}

		last = num;
		if(d == 2)
			d = 3;

		else if(d == 3)
			d = 5;

		else
		{
			d += k;
			k = 6 - k;
		}
	}

	if(num > 1)
	{
		res = 1;
		pos = result.lower_bound(pair<long long unsigned int, unsigned short int>(num, 0));
		if(pos != result.end() && pos->first == num)
		{
			res += pos->second;
			result.erase(pos);
			best.erase(pair<unsigned short int, long long unsigned int>(pos->second, pos->first));
		}

		result.insert(pair<long long unsigned int, unsigned short int>(num, res));
		best.insert(pair<unsigned short int, long long unsigned int>(res, num));
		num = 1;
	}
}
/*
inline void factorizeShanks(long long unsigned int &num)
{
	if(num == 1)
		return;

	if((long long unsigned int)sqrt(num) * (long long unsigned int)sqrt(num) == num)
	{
		res = 2;
		pos = result.lower_bound(pair<long long unsigned int, unsigned short int>(sqrt(num), 0));
		if(pos != result.end() && pos->first == num)
		{
			res += pos->second;
			result.erase(pos);
			best.erase(pair<unsigned short int, long long unsigned int>(pos->second, pos->first));
		}

		result.insert(pair<long long unsigned int, unsigned short int>(sqrt(num), res));
		best.insert(pair<unsigned short int, long long unsigned int>(res, sqrt(num)));
		num = 1;
		return;
	}

	if(checkPrime(num))
	{
		res = 1;
		pos = result.lower_bound(pair<long long unsigned int, unsigned short int>(num, 0));
		if(pos != result.end() && pos->first == num)
		{
			res += pos->second;
			result.erase(pos);
			best.erase(pair<unsigned short int, long long unsigned int>(pos->second, pos->first));
		}

		result.insert(pair<long long unsigned int, unsigned short int>(num, res));
		best.insert(pair<unsigned short int, long long unsigned int>(res, num));
		num = 1;
		return;
	}

	long long unsigned int P[3],
						   Q[3],
						   B[3],
						   divisor;
	int i = 0;
	P[0] = sqrt(num);
	Q[0] = 1;
	Q[1] = num - P[0] * P[0];
	for(i = 1; (long long unsigned int)sqrt(Q[i]) * (long long unsigned int)sqrt(Q[i]) != Q[i]; i = (i + 1) % 3)
	{
		B[i] = ((long long unsigned int)sqrt(num) + P[(2 + i) % 3]) / Q[i];
		P[i] = B[i] * Q[i] - P[(2 + i) % 3];
		Q[(i + 1) % 3] = Q[(2 + i) % 3] + B[i] * (P[(2 + i) % 3] - P[i]);
	}

	B[0] = ((long long unsigned int)sqrt(num) - P[(2 + i) % 3]) / (long long unsigned int)sqrt(Q[i]);
	P[0] = B[0] * (long long unsigned int)sqrt(num) + P[(2 + i) % 3];
	Q[0] = sqrt(Q[i]);
	Q[1] = (num - P[0] * P[0]) / Q[0];
	for(i = 1; P[(i + 1) % 3] != P[i] && P[i] != P[(i + 2) % 3]; i = (i + 1) % 3)
	{
		B[i] = ((long long unsigned int)sqrt(num) + P[(2 + i) % 3]) / Q[i];
		P[i] = B[i] * Q[i] - P[(2 + i) % 3];
		Q[(i + 1) % 3] = Q[(2 + i) % 3] + B[i] * (P[(2 + i) % 3] - P[i]);
	}

	divisor = gcd(num, P[i]);
	if(divisor == 1)
		return; // Nie znalazło dzielnika...

	process(divisor);
	num /= divisor;
	process(num);
	return;
}
*/
inline long long unsigned int gcd(long long unsigned int A, long long unsigned int B)
{
	if(A < B)
		swap(A, B);

	long long unsigned int C;
	while(B)
	{
		C = B;
		B = A % B;
		A = C;
		if(A < B)
			swap(A, B);
	}

	return A;
}
