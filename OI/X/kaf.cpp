/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<string>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

class BigInt
{
	private:
		int repr[512];
		int size;

	public:
		BigInt(void);
		BigInt(char *in);

		inline std::string toString(void) const;

		inline BigInt operator+(const BigInt &a) const;
		inline BigInt operator-(const BigInt &a) const;
		inline BigInt operator/(const int &a) const;
		inline BigInt operator*(const int &a) const;
		inline int operator%(const int &a) const;
		inline bool operator>(const BigInt &a) const;
		inline bool operator!(void) const;
};

char buf[512];

BigInt length,
	   repeatA,
	   repeatB,
	   nwd,
	   L,
	   R;

inline BigInt bNWD(BigInt a, BigInt b);

int main(void)
{
	scanf("%s", buf);
	length = BigInt(buf);
	scanf("%s", buf);
	repeatA = BigInt(buf);
	scanf("%s", buf);
	repeatB = BigInt(buf);

	nwd = bNWD(repeatA, repeatB);
	L = nwd + length;
	R = repeatA + repeatB;
	printf("%s\n", (L > R?nwd:R - length).toString().c_str());
	return 0;
}

inline BigInt bNWD(BigInt a, BigInt b)
{
	int ndPow = 0;
	while(!!b)
	{
		if(b > a)
			std::swap(a, b);

		if(!(a % 2) && !(b % 2))
		{
			++ ndPow;
			a = a / 2;
			b = b / 2;
		}

		else if(!(a % 2))
			a = a / 2;

		else if(!(b % 2))
			b = b / 2;

		else
			a = (a - b) / 2;
	}

	while(ndPow --)
		a = a * 2;

	return a;
}

BigInt::BigInt(void)
{
	this->size = 0;
	for(int r = 0; r < 512; ++ r)
		this->repr[r] = 0;

	return;
}

BigInt::BigInt(char *in)
{
	this->size = 0;
	while(in[this->size])
		++ this->size;

	for(int i = 0; i < this->size; ++ i)
		this->repr[i] = in[this->size - 1 - i] - '0';

	return;
}

inline std::string BigInt::toString(void) const
{
	if(!this->size)
		return "0";

	std::string res;
	for(int s = this->size - 1; s >= 0; -- s)
		res += this->repr[s] + '0';

	return res;
}

inline bool BigInt::operator!(void) const
{
	return !this->size;
}

inline int BigInt::operator%(const int &a) const
{
	return this->repr[0] % a;
}

inline bool BigInt::operator>(const BigInt &a) const
{
	if(this->size > a.size)
		return true;

	if(this->size < a.size)
		return false;

	for(int r = this->size; r; -- r)
		if(this->repr[r] != a.repr[r])
			return this->repr[r] > a.repr[r];

	return this->repr[0] > a.repr[0];
}

inline BigInt BigInt::operator+(const BigInt &a) const
{
	BigInt res;
	int rest = 0,
		s = this->size > a.size?this->size:a.size;
	for(int r = 0; r < s; ++ r)
	{
		res.repr[r] = rest + this->repr[r] + a.repr[r];
		rest = res.repr[r] / 10;
		res.repr[r] %= 10;
	}

	res.repr[s] = rest;
	res.size = s + !!rest;
	return res;
}

inline BigInt BigInt::operator-(const BigInt &a) const
{
	/* XXX: this >= a */
	BigInt res;
	for(int r = 0; r < this->size; ++ r)
	{
		res.repr[r] += this->repr[r] - a.repr[r];
		while(res.repr[r] < 0)
		{
			res.repr[r] += 10;
			res.repr[r + 1] -= 1;
		}
	}

	res.size = this->size;
	while(res.size && !res.repr[res.size - 1])
		-- res.size;

	return res;
}

inline BigInt BigInt::operator*(const int &a) const
{
	BigInt res;
	int rest = 0;
	for(int r = 0; r < this->size; ++ r)
	{
		res.repr[r] = rest + this->repr[r] * a;
		rest = res.repr[r] / 10;
		res.repr[r] %= 10;
	}

	res.repr[this->size] = rest;
	res.size = this->size + !!rest;
	return res;
}

inline BigInt BigInt::operator/(const int &a) const
{
	BigInt res;
	for(int r = this->size - 1, act = 0; r >= 0; -- r)
	{
		act *= 10;
		act += this->repr[r];
		res.repr[r] = act / a;
		act %= a;
	}

	res.size = this->size;
	while(res.size && !res.repr[res.size - 1])
		-- res.size;

	return res;
}
