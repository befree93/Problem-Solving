#include <iostream>
#include<string.h>
#include<vector>
using namespace std;
#define  MOD  3LL
typedef  long long ll;
int top;
ll degSum[35];//차수의 부분합
typedef struct trinomial
{
    ll deg;
    ll coef;
}trinomial;

vector<vector<trinomial>> tr;//다항식
void init(ll n)//n을 3진법으로 나누어주면 다항식 처리
{
    ll nn, d = 1;
    while (n)
    {
        nn = n%MOD;
        if (nn == 1)
        {
            degSum[top] += d * 2;
            tr[top].push_back({ d * 2,1 });
            tr[top].push_back({ d,1 });
            tr[top++].push_back({ 0,1 });
            degSum[top] = degSum[top - 1];
        }
        else if (nn == 2)
        {
            degSum[top] += d * 4;
            tr[top].push_back({ d * 4,1 });
            tr[top].push_back({ d * 3,2 });
            tr[top].push_back({ d,2 });
            tr[top++].push_back({ 0,1 });
            degSum[top] = degSum[top - 1];
        }
        n /= MOD; d *= MOD;
    }
}
int get_coef(int now, int c, ll m)
{
    int ret = 0;
    if (m == 0)return c;//차수 만족
    if (now<0)return 0;//만족하는 차수없음
    for (int i = 0; i < tr[now].size(); i++)
    {
        if (m - tr[now][i].deg > degSum[now - 1])break; //현재차수+나머지항들의 차수가 구해야할 차수보다 작은 경우
        if (tr[now][i].deg > m)continue;//현재차수가 구해야할 차수보다 클 경우
        ret += get_coef(now - 1, (tr[now][i].coef*c) % MOD, m - tr[now][i].deg) % MOD;
        ret %= MOD;
    }
    return ret;
}
int main(void)
{
    int T;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++)
    {
        ll N, K;
        top = 1; degSum[0] = 1e16;
        tr.clear();tr.resize(32);
        scanf("%lld %lld", &N, &K);
        printf("#%d ", tc);
        if (K > N)K = 2 * N - K;
        if (K == 0 || N <= 1)puts("1");
        else
        {
            init(N);
            printf("%d\n", get_coef(top - 1, 1, K));
        }
        for (int i = 1; i < top; i++)degSum[i] = 0;
    }
    return 0;
}
