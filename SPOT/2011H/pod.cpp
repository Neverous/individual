/* 2011
 * Maciej Szeptuch
 * -*-*-*-*-*-*-*-*-
 */
#include<cstdio>
#include<vector>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	verts,
	edges,
	dividers[64],
	start, end,
	prime[64] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263};

long long unsigned int value[64];

bool visited[64];

std::vector<int> graph[64];

class bInt
{
	private:
		int data[1024];
		int length;

	public:
		bInt(void);
		bInt operator*=(const int &b);
		bInt operator=(const int &b);
		void print(void);
};

bool solve(void)
{
	int count = verts,
		primes = 0;
	bool done = true;
	while(count && done)
	{
		done = false;
		for(int v = 0; v < verts; ++ v)
		{
			if(dividers[v] || visited[v])
				continue;

			visited[v] = true;
			done = true;
			-- count;

			for(unsigned int n = 0; n < graph[v].size(); ++ n)
			{
				if((value[graph[v][n]] & value[v]) != value[v])
					return false;

				value[graph[v][n]] |= 1LLU << primes;
				-- dividers[graph[v][n]];
			}

			value[v] |= 1LLU << (primes ++);
		}
	}

	if(count && !done)
		return false;

	puts("TAK");
	for(int v = 0; v < verts; ++ v)
	{
		bInt val;
		for(int m = 0; m < 64; ++ m)
			if((1LLU << m) & value[v])
				val *= prime[m];

		val.print();
	}

	return true;
}

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %d", &verts, &edges);
		for(int v = 0; v < verts; ++ v)
		{
			graph[v].clear();
			dividers[v] = 0;
			value[v] = 0;
			visited[v] = false;
		}

		for(int e = 0; e < edges; ++ e)
		{
			scanf("%d %d", &start, &end);
			-- start;
			-- end;
			graph[start].push_back(end);
			++ dividers[end];
		}

		if(!solve())
			puts("NIE");
	}

	return 0;
}

bInt::bInt(void)
{
	for(int v = 0; v < 1024; ++ v)
		this->data[v] = 0;

	this->data[0] = 1;
	this->length = 1;
	return;
}

bInt bInt::operator*=(const int &b)
{
	int d = 0;
	for(int rest = 0; d < this->length || rest; ++ d)
	{
		this->data[d] = this->data[d] * b + rest;
		rest = this->data[d] / 10;
		this->data[d] %= 10;
	}

	this->length = d;

	return *this;
}

void bInt::print(void)
{
	for(int d = this->length - 1; d >= 0; -- d)
		putchar('0' + this->data[d]);

	puts("");
	return;
}
