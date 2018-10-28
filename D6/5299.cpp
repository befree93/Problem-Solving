#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long ll;
int main()
{
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		ll n, i,sum=0;
		scanf("%lld", &n);
		for (i=2; i*i<n; i++)//제곱수 이상으로 표현 가능한경우
		{
			ll m = n / i, k =1,t=1;
				while (m)
				{
					t *= i;
					k += t;
					m /= i;
					sum += (m) ? ((i-1)*i) : (n/k)*i;
          //다음비트가 존재하면 i-1만큼 i를 더해주고,
          //없다면 1로이루어진 균일수로 n을 나눈 것만큼 더해준다.
				}
		}
		for (ll j = 1; j*j < n; j++)//제곱수로 나타낼수 있는경우
		{
			ll x = (n - j) / j;
			if (x < j)break;
			sum += (x - i + 1)*(i + x) / 2;//등차수열의 합
		}
		printf("#%d %lld\n", tc, sum);
	}
	return 0;
}
