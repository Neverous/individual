/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <cctype>

int k,
    realpos[1024],
    t;
char sentence[1024];

int main(void)
{
    while(scanf("%d %[^\n]", &k, sentence) != -1)
    {
        int result = 0,
            resultPos = 0;
        int p = 0;
        for(int s = 0; sentence[s]; ++ s)
        {
            realpos[p] = s;
            if(isalpha(sentence[s]))
            {
                if('A' <= sentence[s]  && sentence[s] <= 'Z')
                    sentence[s] -= 'A' - 'a';

                sentence[p ++] = sentence[s];
            }
        }

        sentence[p] = 0;
        for(p = 0; sentence[p]; ++ p)
        {
            {
                int len = 1;
                int diff = 0;
                while(p - len >= 0 && sentence[p + len] && (
                    sentence[p - len] == sentence[p + len] || diff ++ < k))
                    ++ len;

                -- len;
                if(realpos[p + len] - realpos[p - len] + 1 > result)
                {
                    result = realpos[p + len] - realpos[p - len] + 1;
                    resultPos = realpos[p - len];
                }
            }

            {
                int len = 0;
                int diff = 0;
                while(p - len - 1 >= 0 && sentence[p + len] && (
                    sentence[p - len - 1] == sentence[p + len] || diff ++ < k))
                    ++ len;

                -- len;
                if(realpos[p + len] - realpos[p - len - 1] + 1 > result)
                {
                    result = realpos[p + len] - realpos[p - len - 1] + 1;
                    resultPos = realpos[p - len - 1];
                }
            }
        }

        printf("Case %d: %d %d\n", ++ t, result, resultPos + 1);
    }

    return 0;
}
