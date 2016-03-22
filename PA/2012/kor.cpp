/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <vector>

#define CONST 4000

int rails;
long long int rail[1048576];

std::vector<long long int> temp[3];

inline const int $(const int &a){return (3 + a % 3) % 3;}

int main(void)
{
    scanf("%d", &rails);
    temp[0].resize(rails);
    temp[1].resize(rails - 1);
    //printf("0: ");
    for(int r = 1; r <= rails; ++ r) // POZIOM 0, WNN
    {
        scanf("%lld", &temp[0][r - 1]);
        rail[r] = rail[r - 1] + temp[0][r - 1];
        //printf("%lld ", temp[0][r - 1]);
    }

    //printf("\n1: ");
    for(int r = 0; r < rails - 1; ++ r) // POZIOM 1, WN(N+1)
    {
        temp[1][r] = temp[0][r] + temp[0][r + 1];
        //printf("%lld ", temp[1][r]);
    }

    for(int l = 2; l < rails; ++ l) // POZIOM L, WN(N+L)
    {
        //printf("\n%d: ", l);
        temp[$(l)].resize(rails - l);
        for(int r = 0; r < rails - l; ++ r)
        {
            temp[$(l)][r] = rail[r+1+l] - rail[r] - std::min(temp[$(l-1)][r], std::min(temp[$(l-1)][r+1], temp[$(l-2)][r+1]));
            //printf("%lld[%lld, %lld, %lld] ", temp[$(l)][r], temp[$(l-1)][r], temp[$(l-2)][r+1], temp[$(l-1)][r+1]);
        }
    }

    //puts("");
    printf("%lld %lld\n", temp[$(rails - 1)][0], rail[rails] - temp[$(rails - 1)][0]);
    return 0;
}
