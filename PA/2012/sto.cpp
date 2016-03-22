/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <algorithm>

using namespace std;

long long int width,
              height,
              chair;

int main(void)
{
    scanf("%lld %lld %lld", &width, &height, &chair);
    printf("%lld\n", min(width / chair, 2LL) * (height / chair) + min(height / chair, 2LL) * (width / chair) - min(height / chair, 2LL) * min(width / chair, 2LL));
}
