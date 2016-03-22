/* 2015
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>

int bills,
    bill,
    sum, min = 1024;

int main(void)
{
    scanf("%d", &bills);
    for(int b = 0; b < bills; ++ b)
    {
        scanf("%d", &bill);
        sum += bill;
        if(bill % 2 && bill < min)
            min = bill;
    }

    sum -= (sum % 2 ? min : 0);
    if(sum)
        printf("%d\n", sum);

    else
        puts("NIESTETY");

    return 0;
}
