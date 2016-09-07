/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>
#include<algorithm>
#include<vector>

int topics,
	questions,
	queries,
	id,
	featured,
	limit;
long double latitude, longitude,
	 		QUERepr[1024];
char type[4];
std::pair<double, double> topic[1024];
std::vector<int> topicList,
				 questionList,
				 topicQuestion[1024],
				 *resultList,
				 question[1024];

inline static bool GPSCompare(const int &a, const int &b)
{
	return std::make_pair((topic[a].first - latitude) * (topic[a].first - latitude) + (topic[a].second - longitude) * (topic[a].second - longitude), -a) < 
		   std::make_pair((topic[b].first - latitude) * (topic[b].first - latitude) + (topic[b].second - longitude) * (topic[b].second - longitude), -b);
}

inline static bool QUECompare(const int &a, const int &b)
{
	return std::make_pair(QUERepr[a], -a) < std::make_pair(QUERepr[b], -b);
}

int main(void)
{
	scanf("%d %d %d", &topics, &questions, &queries);
	for(int t = 0; t < topics; ++ t)
	{
		scanf("%d %Lf %Lf", &id, &latitude, &longitude);
		topic[id] = std::make_pair(latitude, longitude);
		topicList.push_back(id);
	}

	for(int q = 0; q < questions; ++ q)
	{
		scanf("%d %d", &id, &featured);
		if(!featured)
			continue;

		question[id].resize(featured);
		for(int f = 0; f < featured; ++ f)
		{
			scanf("%d", &question[id][f]);
			topicQuestion[question[id][f]].push_back(id);
		}

		questionList.push_back(id);
	}

	for(int q = 0; q < queries; ++ q)
	{
		scanf("%s %d %Lf %Lf", type, &limit, &latitude, &longitude);
		std::sort(topicList.begin(), topicList.end(), GPSCompare);
		if(type[0] == 't') // Topics
			resultList = &topicList;

		else // Questions
		{
			for(int t = 0; t < questions; ++ t)
				QUERepr[t] = 4096;

			for(int t = 0; t < topicList.size(); ++ t)
				for(int s = 0; s < topicQuestion[topicList[t]].size(); ++ s)
					if(QUERepr[topicQuestion[topicList[t]][s]] == 4096)
						QUERepr[topicQuestion[topicList[t]][s]] = (topic[topicList[t]].first - latitude) * (topic[topicList[t]].first - latitude) + (topic[topicList[t]].second - longitude) * (topic[topicList[t]].second - longitude);

			std::sort(questionList.begin(), questionList.end(), QUECompare);
			resultList = &questionList;
		}

		for(int t = 0; t < limit && t < resultList->size(); ++ t)
			printf("%d%c", (*resultList)[t], t + 1 == resultList->size() || t + 1 == limit?'\n':' ');
	}

	return 0;
}
