#include <bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define pb push_back
using namespace std;
const int maxn=5e3+5;
int n,m;
string a,b;
int f[maxn][maxn];
int main()
{
//    freopen("1.txt","r",stdin);
    cin>>a>>b;
    n=a.length();
    m=b.length();
    a=' '+a;
    b=' '+b;
 
    memset(f,63,sizeof f);
    f[0][0]=0;
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            if(f[i][j]>=0){
                //add
                f[i][j+1]=min(f[i][j+1],f[i][j]+1);
                //remove
                f[i+1][j]=min(f[i+1][j],f[i][j]+1);
                //replace
                f[i+1][j+1]=min(f[i+1][j+1],f[i][j]+(a[i+1]!=b[j+1]));
            }
        }
    }
    cout<<f[n][m];
}