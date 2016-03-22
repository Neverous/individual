/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <cstring>

int students,
    queries,
    position,
    distance[2][128];
char name[128][4],
     step[2][16] = {"right of ", "left of "};

inline int abs(int a){return a>0?a:-a;}
void preprocess(void);
char *makeAnswer(int pos, char *output);

int main(void)
{
    scanf("%d", &students);
    for(int s = 0; s < students; ++ s)
        scanf("%s", name[s]);

    preprocess();
    scanf("%d", &queries);
    for(int q = 0; q < queries; ++ q)
    {
        scanf("%d", &position);
        char output[16384] = {};
        puts(makeAnswer(position - 1, output));
    }

    return 0;
}

void preprocess(void)
{
    int dist = 1000;
    for(int s = 0; s < students; ++ s)
    {
       if(name[s][0] != '?')
           dist = 0;

       distance[0][s] = dist ++;
    }

    dist = 1000;
    for(int s = students - 1; s >= 0; -- s)
    {
        if(name[s][0] != '?')
            dist = 0;

        distance[1][s] = dist ++;
    }
}

char *makeAnswer(int pos, char *output)
{
    if(distance[0][pos] == 0)
        return name[pos];

    int o = 0;
    if(distance[0][pos] == distance[1][pos])
    {
        strcpy(output, "middle of "); o = 10;
        char *nm = name[pos - distance[0][pos]];
        while(*nm)
            output[o ++] = *nm ++;

        strcpy(output + o, " and "); o += 5;
        nm = name[pos + distance[1][pos]];
        while(*nm)
            output[o ++] = *nm ++;

        output[o ++] = 0;
        return output;
    }

    int direction = distance[0][pos] > distance[1][pos];
    for(int i = 0; i < distance[direction][pos]; ++ i)
    {
        char *st = step[direction];
        while(*st)
            output[o ++] = *st ++;
    }

    char *nm = name[pos + (direction?distance[1][pos]:-distance[0][pos])];
    while(*nm)
        output[o ++] = *nm ++;

    output[o ++] = 0;
    return output;
}
