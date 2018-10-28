#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
#define MAXN 100002

int p[MAXN], lev[MAXN],W[MAXN];
void uf_init(int n) { for (int i = 1; i <=n; i++)p[i] = i, lev[i] = W[i] = 0; }
int uf_find(int a )
{
	if (a == p[a]) return a;
	W[a] += W[p[a]]; //부모노드 보다 x만큼 무거우므로 추가 
	return p[a] = uf_find(p[a]);
}

void uf_merge(int a, int b,int w)
{
	int pa = uf_find(a);//작은무게
	int pb = uf_find(b);//큰 무게

	if (pa == pb)return;
	if (lev[pa] < lev[pb]) { //무게가 큰쪽이 더 깊다면
		p[pa] = pb;
		W[pa] = W[b] - W[a] - w; //가벼운쪽의 부모노드 무게 w만큼 뺸다 (W[a]+w 만큼 가볍움)
	}
	else { //같거나 a(작은쪽)이 더 많다면
		p[pb] = pa;
		W[pb] = -W[b]+(W[a] + w); //큰무게의  부모노드 몸무게에 w만큼 추가
		if (lev[pa] == lev[pb])lev[pa]++;
	}
}

int main()
{
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int n, m;
		scanf("%d %d", &n, &m);
		uf_init(n);
		printf("#%d ", t);
		while (m--) {
			char s;
			int x, y,w;
			scanf(" %c %d %d", &s, &x, &y);
			if (s == '!') {
				scanf("%d", &w);
				uf_merge(x, y,w);
			}
			else {
				if (uf_find(x)==uf_find(y))printf("%d ",W[y]-W[x]);
				else printf("UNKNOWN ");
				}
			}
		printf("\n");
		}
	return 0;
}
