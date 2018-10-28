#include<stdio.h>
#include<string.h>
#include<vector>
#include<algorithm>
#include<math.h>
using namespace std;
#define MOD 1000000007
#define MAXN 100002
int sz, arr[MAXN], cnt[MAXN * 10];
long long sum,ans[MAXN];
typedef struct
{
	int lo, hi, idx;
}querry;
querry Q[MAXN];
bool cmp(const querry &a, const querry &b)
{
	int l = a.hi / sz;
	int r = b.hi / sz;
	return l == r ? a.lo < b.lo : l < r;
}

 long long cal(int x,int y)
{
	return (long long)x*(2*y-1);
}
void add(int val)
{
	sum += cal(val, ++cnt[val]);
}
void erase(int val)
{
	sum -= cal(val, cnt[val]--);
}
int solve(int n,int m)
{
	int lo = 1, hi = 1,ret=0;
	sz = sqrt(n);
	sort(Q, Q + m, cmp);
	add(arr[1]);
	for (int i = 0; i < m; i++)
	{
		int nlo = Q[i].lo, nhi = Q[i].hi;
		for (int j = lo; j < nlo; j++)erase(arr[j]);
		for (int j = lo - 1; j >= nlo; j--)add(arr[j]);
		for (int j = hi+1; j <= nhi; j++)add(arr[j]);
		for (int j = hi; j > nhi; j--)erase(arr[j]);
		lo = nlo; hi = nhi;
		ans[Q[i].idx] = sum%MOD;
	}
	for (int i = 0; i < m; i++)
	{
		ret += (ans[i] * (i + 1)) % MOD;
		ret %= MOD;
	}
	return ret;
}
int main()
{
	int T; scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		int n, m; scanf("%d %d", &n, &m);
		memset(cnt, 0, sizeof(cnt)); sum = 0;
		for (int i = 1; i <= n; i++)scanf("%d", arr + i);
		for (int i = 0; i < m; i++)
		{
		 scanf("%d %d", &Q[i].lo, &Q[i].hi);
			Q[i].idx = i;
		}
		printf("#%d %d\n", tc, solve(n, m));
	}
	return 0;
}