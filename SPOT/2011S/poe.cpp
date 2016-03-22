/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<map>
#include<string>
#include<vector>

int tests,
	words,
	pos,
	result;
char buffer[16];
std::string word;

std::map<std::string, std::vector<int> > begin[10],
										 end[10];
std::vector<int> *A,
				 *B;

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d", &words);
		for(int s = 0; s < 10; ++ s)
		{
			begin[s].clear();
			end[s].clear();
		}

		for(int w = 0; w < words; ++ w)
		{
			scanf("%s", buffer);
			word = std::string(buffer);
			for(unsigned int s = 1; s <= word.size(); ++ s)
				begin[s - 1][word.substr(0, s)].push_back(w);

			for(unsigned int s = 1; s <= word.size(); ++ s)
				end[s - 1][word.substr(word.size() - s)].push_back(w);
		}

		scanf("%d", &words);
		for(int w = 0; w < words; ++ w)
		{
			scanf("%s", buffer);
			word = std::string(buffer);
			pos = word.find('*');
			result = 0;
			if(!pos)
				result = end[word.size() - 2][word.substr(1)].size();

			else if(pos + 1 == word.size())
				result = begin[pos - 1][word.substr(0, pos)].size();

			else
			{
				A = &begin[pos - 1][word.substr(0, pos)];
				B = &end[word.size() - pos - 2][word.substr(pos + 1)];

				for(unsigned int a = 0, b = 0; a < A->size() && b < B->size(); ++ a, ++ b)
				{
					while(a < A->size() && b < B->size() && (*A)[a] != (*B)[b])
						if((*A)[a] < (*B)[b])
							++ a;

						else
							++ b;

					if(a < A->size() && b < B->size() && (*A)[a] == (*B)[b])
						++ result;
				}
			}

			printf("%d\n", result);
		}
	}

	return 0;
}

