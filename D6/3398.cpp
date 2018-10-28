#include<stdio.h>
#include<string.h>
#define MAXD 100002
int C[MAXD], K[MAXD];
long long tree[MAXD]; 
struct FWT {
	int size;
	int init(int n) { for (int i = 0; i <= n; i++)tree[i] = 0; return size = n; }
	void update(int i, int diff)
	{
		while (i <= size) {
			tree[i] += diff;
			i += (i&-i);
		}
	}
	long long sum(int idx)
	{
		long long ret = 0;
		while (idx > 0) {
			ret += tree[idx];
			idx -= (idx&-idx);
		}
		return ret;
	}
}ft;
int main()
{
	int T; scanf("%d", &T);
	int n, d;
	long long s, a, b;
	for (int t = 1; t <= T; t++) {
		scanf("%d %d %lld %lld %lld", &n, &d, &s, &a, &b);
		long long ans = 0;
		int start = 0, end;
		ft.init(n);
		for (int i = 1; i <= d; i++) {
			C[i] = s % n + 1; s = (s*a + b) % 1000000007;
			K[i] = s % n + 1; s = (s*a + b) % 1000000007;
			if (C[i] == n)ft.update(1, i);
			else {
				end = (start + C[i] - 1) % n;
				ft.update(start + 1, i);
				if (end < start)ft.update(1, i), ft.update(end + 2, -i);
				else if (end < n - 1)ft.update(end + 2, -i);
				start = (end + 1) % n;
			}
			ans += ft.sum(((start + K[i] - 1) % n) + 1);
		}
		printf("#%d %lld\n", t, ans);
	}
	return 0;
}
