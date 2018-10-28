#include<stdio.h>
struct Trie
{
	Trie *child[26];
	int child_cnt;
	int end_cnt;
	Trie()
	{
		 child_cnt = end_cnt=0;
		for (int i = 0; i < 26; i++)
			child[i] = 0;
	}
	~Trie()
	{
		for (int i = 0; i < 26; i++)
			if (child[i])delete child[i];
	}
	void insert(const char *key,int cnt)
	{
		child_cnt++;
		if (*key == '\0')
		{
			end_cnt = cnt+child_cnt;
			return;
		}
		int next = *key - 'a';
		if (!child[next]) child[next] = new Trie();
		child[next]->insert(key + 1, cnt + child_cnt);
	}
	int querry(const char *key,int cnt)
	{

		if (*key == '\0')
		{
			return end_cnt ? end_cnt : cnt + child_cnt;
		}
		int next = *key - 'a';
		if (!child[next]) return cnt+child_cnt;
		return child[next]->querry(key + 1, cnt+child_cnt);
	}
};

int main()
{
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		int n,m;
		Trie root;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
		{
			char buf[21];
			scanf("%s", buf);
			root.insert(buf,0);
		}
		scanf("%d", &m);
		long long ans = 0;
		for (int i = 0; i < m; i++)
		{
			char buf[21];
			scanf("%s", buf);
			ans += root.querry(buf, 0);
		}
		printf("#%d %lld\n",tc, ans);
	}
	return 0;
}
