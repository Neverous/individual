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
		const static int SIZE = 1 << 16;
		int data[2 * SIZE];

	public:
		Tree(void);
		inline void clear(void);
		inline void setValue(int pos, const int &value);
		inline int getSum(int start = 1, int end = SIZE, int iStart = 1, int iEnd = SIZE, int index = 1);
};

int numbers,
	inv,
	result,
	number[50005],
	dp[2][50005];

Tree tree;

int main(void)
{
	scanf("%d %d", &numbers, &inv);
	for(int n = 1; n <= numbers; ++ n)
	{
		scanf("%d", &number[n]);
		dp[0][n] = 1;
	}

	for(int i = 1; i < inv; ++ i)
	{
		tree.clear();
		for(int n = 1; n <= numbers; ++ n)
		{
			dp[i & 1][n] = tree.getSum(number[n] + 1);
			tree.setValue(number[n], dp[(i ^ 1) & 1][n]);
		}
	}

	for(int n = 1; n <= numbers; ++ n)
		result = (result + dp[(inv ^ 1) & 1][n]) % 1000000007;

	printf("%d\n", result);
	return 0;
}

Tree::Tree(void)
{
	this->clear();
	return;
}

inline void Tree::clear(void)
{
	for(int s = 0; s < 2 * this->SIZE; ++ s)
		this->data[s] = 0;

	return;
}

inline void Tree::setValue(int pos, const int &value)
{
	pos += this->SIZE;
	this->data[pos] = value;
	pos /= 2;
	while(pos)
	{
		this->data[pos] = (this->data[pos * 2] + this->data[pos * 2 + 1]) % 1000000007;
		pos /= 2;
	}

	return;
}

inline int Tree::getSum(int start, int end, int iStart, int iEnd, int index)
{
	if(start == iStart && end == iEnd)
		return this->data[index];

	int iMiddle = (iStart + iEnd) / 2;
	if(end <= iMiddle)
		return this->getSum(start, end, iStart, iMiddle, index * 2);

	if(start > iMiddle)
		return this->getSum(start, end, iMiddle + 1, iEnd, index * 2 + 1);

	return (this->getSum(start, iMiddle, iStart, iMiddle, index * 2) +
			this->getSum(iMiddle + 1, end, iMiddle + 1, iEnd, index * 2 + 1)) % 1000000007;
}
