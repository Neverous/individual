/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

class Bitset
{
	private:
		long long unsigned int data[80];

	public:
		Bitset(void);
		inline void clear(const bool &value);
		inline void set(const int &pos, const bool &value);
		inline const bool get(const int &pos) const;
		inline const int popcount(void) const;
		inline Bitset operator|=(const Bitset &A);
		inline Bitset operator&=(const Bitset &A);
		inline bool operator!=(const Bitset &A);
		inline Bitset operator=(const Bitset &A);
};

int verts,
	edges,
	start,
	end,
	result;
std::vector<int> graph[5005];
bool changed;
Bitset dominators[5005],
	   dominator;

int main(void)
{
	scanf("%d %d", &verts, &edges);
	for(int e = 0; e < edges; ++ e)
	{
		scanf("%d %d", &start, &end);
		graph[end - 1].push_back(start - 1);
	}

	dominators[0].set(0, 1);
	for(int v = 1; v < verts; ++ v)
		dominators[v].clear(1);

	changed = true;
	while(changed)
	{
		changed = false;
		for(int v = 1; v < verts; ++ v)
		{
			dominator.clear(1);
			for(unsigned int n = 0; n < graph[v].size(); ++ n)
				dominator &= dominators[graph[v][n]];

			dominator.set(v, 1);
			if(dominator != dominators[v])
			{
				dominators[v] = dominator;
				changed =  true;
			}
		}
	}

	dominator = dominators[0];
	for(int v = 1; v < verts; ++ v)
	{
		dominators[v].set(v, 0);
		dominator |= dominators[v];
	}

	printf("%d\n", dominator.popcount());
	for(int v = 0; v < verts; ++ v)
		if(dominator.get(v))
			printf("%d ", v + 1);

	puts("");

	return 0;
}

Bitset::Bitset(void)
{
	this->clear(0);
	return;
}

inline void Bitset::clear(const bool &value)
{
	for(int v = 0; v < 80; ++ v)
		this->data[v] = (value?(~0LLU):0);

	return;
}

inline void Bitset::set(const int &pos, const bool &value)
{
	int n = pos / 64,
		bit = pos - n * 64;

	if(value)
		this->data[n] |= (1LLU << bit);

	else
		this->data[n] &= ~(1LLU << bit);

	return;
}

inline const bool Bitset::get(const int &pos) const
{
	int n = pos / 64,
		bit = pos - n * 64;
	return this->data[n] & (1LLU << bit);
}

inline const int Bitset::popcount(void) const
{
	int res = 0;
	for(int v = 0; v < 80; ++ v)
		res += __builtin_popcountll(this->data[v]);

	return res;
}

inline Bitset Bitset::operator|=(const Bitset &A)
{
	for(int v = 0; v < 80; ++ v)
		this->data[v] |= A.data[v];

	return *this;
}

inline Bitset Bitset::operator&=(const Bitset &A)
{
	for(int v = 0; v < 80; ++ v)
		this->data[v] &= A.data[v];

	return *this;
}

inline bool Bitset::operator!=(const Bitset &A)
{
	for(int v = 0; v < 80; ++ v)
		if(this->data[v] != A.data[v])
			return true;

	return false;
}

inline Bitset Bitset::operator=(const Bitset &A)
{
	for(int v = 0; v < 80; ++ v)
		this->data[v] = A.data[v];

	return *this;
}
