#include<stdio.h>
#include<string.h>
char s[1000005];
int fail[1000005];
int main()
{
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		int n; scanf("%d", &n);
		scanf("%s", s);
		memset(fail, 0, sizeof(fail));
		int i = 1, j = 0;
		for (;i < n; i++)
		{
			while (j > 0 && s[i] != s[j])j = fail[j - 1];
			if (s[i] == s[j])fail[i] = ++j;
		}
		printf("#%d %d\n", tc, n - fail[n - 1]);
	}
	return 0;
}
