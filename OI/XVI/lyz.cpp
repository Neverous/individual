/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

class Tree
{
	private:
		static const int SIZE = (1 << 18);
		long long int max[SIZE * 2],
			 prefix[SIZE * 2],
			 suffix[SIZE * 2],
			 sum[SIZE * 2],
			 data[SIZE * 2];

	public:
		Tree(long long int val = 0);
		inline void update(long long int pos, long long int value);
		inline long long int getMax(void) const;
		inline void initialize(long long int val);
};

long long int maxSize,
	 actions,
	 iceskates,
	 tolerance,
	 foot;
long long int count;
Tree tree;

inline static long long int MAX(long long int A, long long int B){return A>B?A:B;}

int main(void)
{
	scanf("%lld %lld %lld %lld", &maxSize, &actions, &iceskates, &tolerance);
	tolerance *= iceskates;
	tree.initialize(-iceskates);

	for(long long int a = 0; a < actions; ++ a)
	{
		scanf("%lld %lld", &foot, &count);
		tree.update(foot, count);
		puts(tree.getMax() <= tolerance?"TAK":"NIE");
	}

	return 0;
}

Tree::Tree(long long int val)
{
	if(val)
		this->initialize(val);

	return;
}

inline void Tree::initialize(long long int val)
{
	for(int s = this->SIZE; s < 2 * this->SIZE; ++ s)
	{
		this->max[s] = this->prefix[s] = this->suffix[s] = 0;
		this->data[s] = this->sum[s] = val;
	}

	for(int s = this->SIZE - 1; s > 0; -- s)
	{
		this->sum[s] = this->sum[s * 2] + this->sum[s * 2 + 1];
		this->suffix[s] = MAX(this->suffix[s * 2 + 1], this->suffix[s * 2] + this->sum[s * 2 + 1]);
		this->prefix[s] = MAX(this->prefix[s * 2], this->sum[s * 2] + this->prefix[s * 2 + 1]);
		this->max[s] = MAX(MAX(this->max[s * 2], this->max[s * 2 + 1]), this->suffix[s * 2] + this->prefix[s * 2 + 1]);
		this->data[s] = 0;
	}

	return;
}

inline void Tree::update(long long int pos, long long int value)
{
	pos += this->SIZE;
	this->data[pos] += value;
	this->max[pos] = this->prefix[pos] = this->suffix[pos] = MAX(0, this->data[pos]);
	this->sum[pos] = this->data[pos];

	pos /= 2;
	while(pos)
	{
		this->sum[pos] = this->sum[pos * 2] + this->sum[pos * 2 + 1];
		this->suffix[pos] = MAX(this->suffix[pos * 2 + 1], this->suffix[pos * 2] + this->sum[pos * 2 + 1]);
		this->prefix[pos] = MAX(this->prefix[pos * 2], this->sum[pos * 2] + this->prefix[pos * 2 + 1]);
		this->max[pos] = MAX(MAX(this->max[pos * 2], this->max[pos * 2 + 1]), this->suffix[pos * 2] + this->prefix[pos * 2 + 1]);
		pos /= 2;
	}

	return;
}

inline long long int Tree::getMax(void) const
{
	return this->max[1];
}
