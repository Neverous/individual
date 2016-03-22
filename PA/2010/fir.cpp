/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<list>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

struct WorkerNode
{
	int id;
	WorkerNode *ancestor[20];
	std::list<WorkerNode *> offspring[20];

	WorkerNode(int Id = 0)
	{
		id = Id;
		for(int l = 0; l < 20; ++ l)
		{
			ancestor[l] = 0;
			offspring[l].clear();
		}
	}

	inline int getId(void)
	{
		return id;
	}

	inline WorkerNode *appendWorker(int Id) // Dodaj bezpośredniego podwładnego
	{
		WorkerNode *worker = new WorkerNode(Id),
				   *actual = this;

		for(int l = 0; actual != 0; ++ l)
		{
			actual->appendOffspring(worker, l);
			worker->setAncestor(actual, l);
			actual = actual->getAncestor(l);
		}

		return worker;
	}

	void appendOffspring(WorkerNode *worker, int level) // Ustaw potomka
	{
		offspring[level].push_back(worker);
	}

	inline void setAncestor(WorkerNode *worker, int level) // Ustaw przodka
	{
		ancestor[level] = worker;
	}

	inline WorkerNode *getAncestor(int level) // Pobierz odpowiedniego przodka
	{
		if(level > 19)
			return 0;

		return ancestor[level];
	}

	int countKthWorkers(int k) // Ile podwładnych na poziomie k
	{
		int result = 0,
			p = 0,
			r = 1;

		while(r * 2 <= k)
		{
			++ p;
			r *= 2;
		}

		if(r == k)
			return offspring[p].size();

		for(std::list<WorkerNode *>::iterator o = offspring[p].begin(); o != offspring[p].end(); ++ o)
			result += (*o)->countKthWorkers(k - r);

		return result;
	}
};

int actions,
	A,
	B;
char action[4];
WorkerNode *root = new WorkerNode(0),
		   *idToNode[100010];

int main(void)
{
	idToNode[0] = root;
	scanf("%d", &actions);
	for(int a = 0; a < actions; ++ a)
	{
		scanf("%s %d %d", action, &A, &B);
		-- A;
		if(action[0] == 'Z')
		{
			-- B;
			idToNode[A] = idToNode[B]->appendWorker(A);
		}

		else
			printf("%d\n", idToNode[A]->countKthWorkers(B + 1));
	}

	return 0;
}

