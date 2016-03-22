/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>

int tests,
	height,
	width,
	circles,
	Sx[1024],
	Sy[1024],
	R[1024],
	repr[1024],
	left[1024],
	right[1024];
bool possible;

inline static const bool circleIntersect(const int &Ax, const int &Ay, const int &Ar, const int &Bx, const int &By, const int &Br);
inline static const int find(const int &v);
inline static const bool join(const int &a, const int &b);

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %d %d", &height, &width, &circles);
		possible = true;
		for(int c = 0; c < circles; ++ c)
		{
			scanf("%d %d %d", &Sy[c], &Sx[c], &R[c]);
			repr[c] = c;
			left[c] = Sx[c] - R[c];
			right[c] = Sx[c] + R[c];
		}

		for(int f = 0; f < circles; ++ f)
			for(int s = f + 1; s < circles; ++ s)
				if(circleIntersect(Sx[f], Sy[f], R[f], Sx[s], Sy[s], R[s]))
					join(f, s);

		for(int c = 0; c < circles; ++ c)
		{
			if(left[find(c)] > Sx[c] - R[c])
				left[find(c)] = Sx[c] - R[c];

			if(right[find(c)] < Sx[c] + R[c])
				right[find(c)] = Sx[c] + R[c];
		}

		for(int c = 0; possible && c < circles; ++ c)
			possible = left[find(c)] > 0 || right[find(c)] < width;

		puts(possible?"TAK":"NIE");
	}

	return 0;
}

inline static const bool circleIntersect(const int &Ax, const int &Ay, const int &Ar, const int &Bx, const int &By, const int &Br)
{
	return (Ar + Br) * (Ar + Br) >= (Ax - Bx) * (Ax - Bx) + (Ay - By) * (Ay - By);
}

inline static const int find(const int &v)
{
	if(repr[v] == v)
		return v;

	return repr[v] = find(repr[v]);
}

inline static const bool join(const int &a, const int &b)
{
	const int rA = find(a),
			  rB = find(b);

	if(rA == rB)
		return false;

	repr[rA] = rB;
	return true;
}
