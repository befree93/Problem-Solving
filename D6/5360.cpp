#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
#define MAXN 100005
//사이클안의 노드로 들어오는 간선의비용,내향그래프개수,내향그래프최대값,SCC그룹번호,사이클밖의 간선과 안의간선의 차이
int cycle[MAXN],ind[MAXN],indMax[MAXN],sn[MAXN],minGap[MAXN];
int minCost[MAXN],cost[MAXN],parent[MAXN];//사이클안의 최소원소,비용,외향간선
long long inCost[MAXN], outCost[MAXN];//사이클원소만 바꿧을때합,바깥원소와 안의원소중 최소값의 힙
struct UnionFind
{
	int *uf;
	UnionFind(int size)
	{
		uf = new int[size + 1];
		for (int i = 1; i <= size; i++)uf[i] = -1;
	}
	~UnionFind()
	{
		delete uf;
	}
	int find(int a)
	{
		if (uf[a] == -1)return a;
		return uf[a] = find(uf[a]);
	}
	bool isCycle(int a, int b)
	{
		a = find(a); b = find(b);
		if (a == b)return true;
		a < b ? uf[b] = a : uf[a] = b;
		return false;
	}
};

int main()
{
	int T; scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		long long ans = 0; int sz = 0;
		int N; scanf("%d", &N);
		memset(sn, 0, sizeof(sn));
		memset(cycle, 0, sizeof(cycle));
		memset(minCost, 0, sizeof(minCost));
		memset(ind, 0, sizeof(ind));
		memset(indMax, 0, sizeof(indMax));
		memset(inCost, 0, sizeof(inCost));
		memset(outCost, 0, sizeof(outCost));
		UnionFind uf(N);
		for (int i = 1; i <= N; i++)minGap[i] = 1e9;
		for (int i = 1; i <= N; i++)
		{
			int x, w;
			scanf("%d %d", &x, &w);
			parent[i] = x;cost[i] = w;
			ind[x]++;
			if (uf.isCycle(i, x))//사이클 존재
			{
				 sn[i] = ++sz;
				minCost[sz] = cost[i];cycle[x] = cost[i];
				for (int t = x; t!= i; t = parent[t])//사이클 업데이트
				{
					sn[t] = sz;
					cycle[parent[t]] = cost[t];
					minCost[sz] = min(minCost[sz], cost[t]);
				}
			}
		}
		for (int i = 1; i <= N; i++)
			if (!cycle[i])//사이클 밖의 원소
			{
				ans += cost[i]; //사이클 밖의 원소 더해줌
				indMax[parent[i]] = max(indMax[parent[i]], cost[i]); //그중의 최대값만빼주면됨,하나일경우 0이됨
			}

		for (int i = 1; i <= N; i++)
		{
			ans -= indMax[i];//들어오는간선중 최대값만빼주기
			if (cycle[i])//사이클인경우
			{
				if (ind[i]>1)//사이클밖의 원소와 안의원소 모두 있음
				{
					int p = sn[i];
					inCost[p] += cycle[i];//사이클원소만바꿧을경우
					if (cycle[i] <= indMax[i])//사이클 깰수 있음
					{
						outCost[p] += cycle[i];
						minCost[p] = 0;		//추가 로 연결안해줘도됨
					}
					else
					{
						outCost[p] += indMax[i];
						minGap[p] = min(minGap[p], cycle[i] - indMax[i]); //사이클밖의원소와 안의원소 차이값의 최소값
					}
				}
			}
		}
		for (int i = 1; i <= sz; i++) {
			outCost[i] += min(minCost[i], minGap[i]); //밖의원소+사이클내의최소원소와 사이클 내부 하나 사용하고 나머지 사용
			if (sz == 1 && inCost[i] == 0)break;//전체가 사이클 하나
			else if (inCost[i] == 0)ans += outCost[i];//사이클 원소끼리만 되어있는 여러 사이클
			else ans += min(inCost[i], outCost[i]);
		}
		printf("#%d %lld\n", tc, ans);
	}
	return 0;
}
