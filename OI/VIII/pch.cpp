/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
/* MAGIC DO NOT TOUCH!!!! */
#include<cstdio>
#include<vector>
#include<algorithm>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

unsigned int tests,
			 verts,
			 next,
			 fWeight[2048],
			 sWeight[2048],
			 fCycles,
			 sCycles,
			 fMin[2048],
			 sMin[2048],
			 fLast[2048],
			 sLast[2048];
std::vector<unsigned int> fGraph[2048],
						  sGraph[2048],
						  fRepr[2048],
						  sRepr[2048],
						  fCycle[2048],
						  sCycle[2048];
bool fProcessed[2048],
	 sProcessed[2048];

inline bool solve(void);
inline bool fReprOperator(const unsigned int &v1, const unsigned int &v2);
inline bool sReprOperator(const unsigned int &v1, const unsigned int &v2);
inline bool fMegaOperator(const std::vector<unsigned int> &v1, const std::vector<unsigned int> &v2);
inline bool sMegaOperator(const std::vector<unsigned int> &v1, const std::vector<unsigned int> &v2);
inline void fCycleDFS(const unsigned int &v, std::vector<unsigned int> &cycle);
inline void sCycleDFS(const unsigned int &v, std::vector<unsigned int> &cycle);
inline bool vectorOperator(const std::vector<unsigned int> &v1, const std::vector<unsigned int> &v2);

int main(void)
{
	scanf("%u", &tests);
	for(unsigned int t = 0; t < tests; ++ t)
	{
		for(unsigned int v = 0; v < 2048; ++ v)
		{
			fProcessed[v] = false;
			sProcessed[v] = false;
			fGraph[v].clear();
			sGraph[v].clear();
			sRepr[v].clear();
			fRepr[v].clear();
			fCycle[v].clear();
			sCycle[v].clear();
			fWeight[v] = 0;
			sWeight[v] = 0;
			fMin[v] = 0;
			sMin[v] = 0;
			fCycles = 0;
			sCycles = 0;
		}

		scanf("%u", &verts);
		for(unsigned int v = 0; v < verts; ++ v)
		{
			scanf("%u", &next);
			-- next;
			fGraph[v].push_back(next);
			fGraph[next].push_back(v);
			++ fWeight[v];
			++ fWeight[next];
		}

		for(unsigned int v = 0; v < verts; ++ v)
		{
			scanf("%u", &next);
			-- next;
			sGraph[v].push_back(next);
			sGraph[next].push_back(v);
			++ sWeight[v];
			++ sWeight[next];
		}

		printf("%c\n", solve()?'T':'N');
	}

	return 0;
}

/* THERE WILL BE DRAGONS ... */

bool solve(void)
{
	std::vector<unsigned int> fQue,
							  sQue;
	for(unsigned int v = 0; v < verts; ++ v)
	{
		if(fWeight[v] == 1)
			fQue.push_back(v);

		if(sWeight[v] == 1)
			sQue.push_back(v);
	}

	while(!fQue.empty() || !sQue.empty())
	{
		if(fQue.size() != sQue.size())
			return false; // Różna ilość wierzchołków na danym poziomie

		for(unsigned int q = 0; q < fQue.size(); ++ q)
		{
			std::sort(fRepr[fQue[q]].begin(), fRepr[fQue[q]].end());
			std::sort(sRepr[sQue[q]].begin(), sRepr[sQue[q]].end());
		} // Uporządkuj reprezentanta (Zamień na numer może?)

		std::sort(fQue.begin(), fQue.end(), fReprOperator);
		std::sort(sQue.begin(), sQue.end(), sReprOperator);
		for(unsigned int q = 0; q < fQue.size(); ++ q)
			if(fRepr[fQue[q]] != sRepr[sQue[q]])
				return false;

		for(unsigned int q = 0, r = 0; q < fQue.size(); ++ q)
		{
			if(q && fRepr[fQue[q]] != fRepr[fQue[q - 1]])
				++ r;

			fProcessed[fQue[q]] = true;
			for(unsigned int f = 0; f < fGraph[fQue[q]].size(); ++ f)
				if(!fProcessed[fGraph[fQue[q]][f]])
				{
					fRepr[fGraph[fQue[q]][f]].push_back(r);
					-- fWeight[fGraph[fQue[q]][f]];
					break;
				}

			sProcessed[sQue[q]] = true;
			for(unsigned int s = 0; s < sGraph[sQue[q]].size(); ++ s)
				if(!sProcessed[sGraph[sQue[q]][s]])
				{
					sRepr[sGraph[sQue[q]][s]].push_back(r);
					-- sWeight[sGraph[sQue[q]][s]];
					break;
				}
		}

		fQue.clear();
		sQue.clear();
		for(unsigned int v = 0; v < verts; ++ v)
		{
			if(!fProcessed[v] && fWeight[v] == 1)
				fQue.push_back(v);

			if(!sProcessed[v] && sWeight[v] == 1)
				sQue.push_back(v);
		}
	}

	/* HERE COMES THE KNWOLEDGE FORGOTTEN FOR CENTURIES */
	for(unsigned int v = 0; v < verts; ++ v)
	{
		if(!fProcessed[v])
			fCycleDFS(v, fCycle[fCycles ++]);

		if(!sProcessed[v])
			sCycleDFS(v, sCycle[sCycles ++]);
	}

	if(fCycles != sCycles)
		return false;

	for(unsigned int c = 0; c < fCycles; ++ c)
	{
		for(unsigned int v = 0; v < fCycle[c].size(); ++ v)
		{
			std::sort(fRepr[fCycle[c][v]].begin(), fRepr[fCycle[c][v]].end());
			fQue.push_back(fCycle[c][v]);
		}

		for(unsigned int v = 0; v < sCycle[c].size(); ++ v)
		{
			std::sort(sRepr[sCycle[c][v]].begin(), sRepr[sCycle[c][v]].end());
			sQue.push_back(sCycle[c][v]);
		}
	}

	if(fQue.size() != sQue.size())
		return false;

	std::sort(fQue.begin(), fQue.end(), fReprOperator);
	std::sort(sQue.begin(), sQue.end(), sReprOperator);
	for(unsigned int q = 0; q < fQue.size(); ++ q)
		if(fRepr[fQue[q]] != sRepr[sQue[q]])
			return false;

	for(unsigned int q = 0, r = 0; q < fQue.size(); ++ q)
	{
		if(q && fRepr[fQue[q]] != fRepr[fQue[q - 1]])
			++ r;

		fLast[fQue[q]] = r;
		sLast[sQue[q]] = r;
	}

	/* I WARNED YOU */
	for(unsigned int c = 0; c < fCycles; ++ c)
	{
		for(unsigned int v = 0; v < fCycle[c].size(); ++ v)
			fCycle[c][v] = fLast[fCycle[c][v]];

		for(unsigned int v = 0; v < sCycle[c].size(); ++ v)
			sCycle[c][v] = sLast[sCycle[c][v]];
	}

	for(unsigned int c = 0, pos = 0; c < fCycles; ++ c)
	{
		for(unsigned int v = 1; v < fCycle[c].size(); ++ v)
		{
			pos = 0;
			while(pos < fCycle[c].size() && fCycle[c][(v + pos) % fCycle[c].size()] == fCycle[c][(fMin[c] + pos) % fCycle[c].size()])
				++ pos;

			if(fCycle[c][(v + pos) % fCycle[c].size()] < fCycle[c][(fMin[c] + pos) % fCycle[c].size()])
				fMin[c] = v;
		}

		fQue.resize(fCycle[c].size());
		pos = 0;
		for(unsigned int v = fMin[c]; v < fCycle[c].size(); ++ v)
			fQue[pos ++] = fCycle[c][v];

		for(unsigned int v = 0; v < fMin[c]; ++ v)
			fQue[pos ++] = fCycle[c][v];

		fCycle[c] = fQue;

		for(unsigned int v = 1; v < sCycle[c].size(); ++ v)
		{
			pos = 0;
			while(pos < sCycle[c].size() && sCycle[c][(v + pos) % sCycle[c].size()] == sCycle[c][(sMin[c] + pos) % sCycle[c].size()])
				++ pos;

			if(sCycle[c][(v + pos) % sCycle[c].size()] < sCycle[c][(sMin[c] + pos) % sCycle[c].size()])
				sMin[c] = v;
		}

		fQue.resize(sCycle[c].size());
		pos = 0;
		for(unsigned int v = sMin[c]; v < sCycle[c].size(); ++ v)
			fQue[pos ++] = sCycle[c][v];

		for(unsigned int v = 0; v < sMin[c]; ++ v)
			fQue[pos ++] = sCycle[c][v];

		sCycle[c] = fQue;
	}

	std::sort(fCycle, fCycle + fCycles, vectorOperator);
	std::sort(sCycle, sCycle + sCycles, vectorOperator);
	for(unsigned int c = 0; c < fCycles; ++ c)
		if(fCycle[c] != sCycle[c])
			return false;

	return true;
}

bool fReprOperator(const unsigned int &v1, const unsigned int &v2)
{
	if(fRepr[v1].size() < fRepr[v2].size())
		return true;

	if(fRepr[v1].size() > fRepr[v2].size())
		return false;

	return fRepr[v1] < fRepr[v2];
}

bool sReprOperator(const unsigned int &v1, const unsigned int &v2)
{
	if(sRepr[v1].size() < sRepr[v2].size())
		return true;

	if(sRepr[v1].size() > sRepr[v2].size())
		return false;

	return sRepr[v1] < sRepr[v2];
}

inline void fCycleDFS(const unsigned int &v, std::vector<unsigned int> &cycle)
{
	cycle.push_back(v);
	fProcessed[v] = true;
	for(unsigned int n = 0; n < fGraph[v].size(); ++ n)
		if(!fProcessed[fGraph[v][n]])
			fCycleDFS(fGraph[v][n], cycle);

	return;
}

inline void sCycleDFS(const unsigned int &v, std::vector<unsigned int> &cycle)
{
	cycle.push_back(v);
	sProcessed[v] = true;
	for(unsigned int n = 0; n < sGraph[v].size(); ++ n)
		if(!sProcessed[sGraph[v][n]])
			sCycleDFS(sGraph[v][n], cycle);

	return;
}

inline bool vectorOperator(const std::vector<unsigned int> &v1, const std::vector<unsigned int> &v2)
{
	if(v1.size() < v2.size())
		return true;

	if(v1.size() > v2.size())
		return false;

	return v1 < v2;
}
