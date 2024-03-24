#include<bits/stdc++.h>
#define dim 7502
#define int long long
using namespace std;
ifstream fin ("graf.in");
ofstream fout("graf.out");
int n,pas[dim],A,B,coada[dim];
bool viz[dim];
vector<int> a[dim],from[dim],sol;
const int INF=2000000000;

void bfs ()
{
    int i,st=1,dr=1;
    for (i=1; i<=n; i++)
        pas[i]=INF;
    pas[A]=0;
    coada[1]=A;
    while (st<=dr)
    {
        int x=coada[st];
        for (auto y:a[x])
        {
            if (pas[x]+1<pas[y])
                coada[++dr]=y;
            if (pas[x]+1<=pas[y])
            {
                pas[y]=pas[x]+1;
                from[y].push_back(x);
            }
        }
        st++;
    }
}

void solve ()
{
    int i,st=1,dr=1;
    coada[1]=B;
    viz[B]=1;
    while (st<=dr)
    {
        int x=coada[st];
        if (st==dr)
            sol.push_back(x);
        for (auto y:from[x])
            if (viz[y]==0)
            {
                viz[y]=1;
                coada[++dr]=y;
            }
        ++st;
    }
    n=sol.size();
    fout<<n<<'\n';
    sort(sol.begin(),sol.end());
    for (i=0;i<n;i++)
        fout<<sol[i]<<' ';

}

int32_t main ()
{
    int m,x,y;
    fin>>n>>m;
    A=1,B=2;
    while (m--)
    {
        fin>>x>>y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    bfs();
    solve ();
    return 0;
}

