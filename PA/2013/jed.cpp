/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <list>

int numbers,
    number,
    target[300001],
    mapping[300001],
    repr[300001],
    result;
std::list<int> bucket[300001];

int main(void)
{
    scanf("%d", &numbers);
    for(int n = 0; n < numbers; ++ n)
    {
        scanf("%d", &number); -- number;
        target[number] = n;
        mapping[n] = -1;
    }

    for(int n = 0; n < numbers; ++ n)
    {
        scanf("%d", &number); -- number;
        int dist = (numbers + target[number] - n) % numbers;
        if(mapping[dist] == -1)
            mapping[dist] = number;

        bucket[mapping[dist]].push_back(number);
    }

    for(int n = 0; n < numbers; ++ n)
        mapping[n] = -1;

    for(int n = 0; n < numbers; ++ n)
    {
        scanf("%d", &number); -- number;
        int dist = (numbers + target[number] - n) % numbers;
        if(mapping[dist] == -1)
            mapping[dist] = number;

        repr[number] = mapping[dist];
    }

    for(int n = 0; n < numbers; ++ n)
    {
        if(bucket[n].empty())
            continue;

        for(std::list<int>::iterator it = bucket[n].begin(); it != bucket[n].end(); ++ it)
            mapping[repr[*it]] = 0;

        while(!bucket[n].empty())
        {
            if(++ mapping[repr[bucket[n].front()]] > result)
                result = mapping[repr[bucket[n].front()]];

            bucket[n].pop_front();
        }
    }

    printf("%d\n", result);
    return 0;
}
