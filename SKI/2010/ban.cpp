/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

class Tree
{
	private:
		static const unsigned int SIZE = 1048576;
		int data[2 * SIZE];

	public:
		Tree(void);
		inline void clear(void);
		inline void insert(unsigned int number, int val = 1);
		inline int getMin(void);
		inline void remove(unsigned int number);
};

unsigned int tests,
			 actions,
			 stack[1000010];
int money,
	st;
long long unsigned int cash,
					   result;
Tree tree;

int main(void)
{
	scanf("%u", &tests);
	for(unsigned int t = 0; t < tests; ++ t)
	{
		scanf("%u %llu", &actions, &cash);
		st = 0;
		tree.clear();
		for(unsigned int a = 0; a < actions; ++ a)
		{
			scanf("%d", &money);
			if(money > 0)
			{
				stack[st ++] = money;
				tree.insert(money);
			}

			else
			{
				if(tree.getMin() > - money)
					cash += money; // wydaj pieniadze z kasy

				else // Wydaj z kopert
				{
					while(money < 0 && st > 0)
					{
						tree.remove(stack[-- st]);
						money += stack[st];
					}

					if(money)
						cash += money;
				}
			}
		}

		result = 0;
		while(-- st >= 0)
			result += stack[st];

		printf("%llu %llu\n", cash, result);
	}

	return 0;
}

Tree::Tree(void)
{
	this->clear();
	return;
}

inline void Tree::clear(void)
{
	for(unsigned int d = 0; d < 2 * this->SIZE; ++ d)
		this->data[d] = 0;

	return;
}

inline void Tree::insert(unsigned int number, int val)
{
	-- number;
	this->data[this->SIZE + number] += val;
	unsigned int p = (this->SIZE + number) / 2;
	if(this->data[p * 2])
		this->data[p] = p * 2;

	else if(this->data[p * 2 + 1])
		this->data[p] = p * 2 + 1;

	else
		this->data[p] = 0;

	p /= 2;
	while(p)
	{
		if(this->data[this->data[p * 2]])
			this->data[p] = this->data[p * 2];

		else if(this->data[this->data[p * 2 + 1]])
			this->data[p] = this->data[p * 2 + 1];

		else
			this->data[p] = 0;

		p /= 2;
	}

	return;
}

inline void Tree::remove(unsigned int value)
{
	this->insert(value, -1);
	return;
}

inline int Tree::getMin(void)
{
	return this->data[1]?this->data[1] - this->SIZE + 1:(1 << 30);
}
