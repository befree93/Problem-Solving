#include<stdio.h>
#include<queue>
#include<string.h>

#define max(a,b) ((a)>(b)?(a):(b))
#define INF 0x7ffffff
#define MAXN 1002
#define MAXM 10002
using namespace std;

typedef struct gp
{
	int x, y, w;
	int prv;
}gp;

long long dist[2][MAXN];
int inQ[MAXN],to[2][MAXN],Q[55*MAXN]; 
int front, rear;
gp g[2][MAXM]; 
int spfa(int s, int l)
{
	Q[front = rear = 0] = s; inQ[s] = 1; dist[l][s] = 0;
	while (front <= rear) {
		int now = Q[front++]; inQ[now] = 0;
		for (int i = to[l][now]; i; i = g[l][i].prv) {
			int next = g[l][i].y;
			int cost = g[l][i].w;
			if (dist[l][next] > cost + dist[l][now]) {
				dist[l][next] = cost + dist[l][now];
				if (!inQ[next]) Q[++rear] = next, inQ[next] = 1;
			}
		}
	}
	return 0;
}

int main()
{
	int N, M, X, t, T;
	scanf("%d", &T);
	for (t = 1; t <= T; t++) {
		scanf("%d %d %d", &N, &M, &X);
		for (int i = 0; i < 2; i++)
			for (int j = 1; j <= N; j++) dist[i][j] = INF, to[i][j] = 0;
		for (int i = 1; i <= M; i++) {
			scanf("%d %d %d", &g[0][i].x, &g[0][i].y, &g[0][i].w);
			g[0][i].prv = to[0][g[0][i].x];
			to[0][g[0][i].x] = i;
			g[1][i].x = g[0][i].y; g[1][i].y = g[0][i].x; g[1][i].w = g[0][i].w;
			g[1][i].prv = to[1][g[1][i].x];
			to[1][g[1][i].x] = i;
		}
		spfa(X, 0); 
		spfa(X, 1); 
		long long ans = 0;
		for (int i = 1; i <= N; i++) ans = max(ans, dist[0][i] + dist[1][i]);
		printf("#%d %d\n", t, ans);
		for (int i = 1; i <= N; i++) inQ[i] = 0;
	}

}
