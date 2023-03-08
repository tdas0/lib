// dada lista com soma de todo par ai+aj,i<j
// recuperar A
// n<=100, ai<=1e9
const int MAXN = 10010;
 
int n;
 
int ans[MAXN];
int v[MAXN], nxt[MAXN];
 
bool solve(int first)
{
    ans[1] = first;
 
    for(int i = 1 ; i <= n ; i++)
        nxt[i] = i + 1;
 
    int qtd = 1;
 
    for(int i = 1 ; 2*i <= n*(n - 1) ; i++)
    {
        bool find = false;
 
        for(int j = 1 ; j <= qtd ; j++)
        {
            if( nxt[j] <= qtd && ans[j] + ans[ nxt[j] ] == v[i] )
            {
                nxt[j]++; find = true;
                break;
            }
        }
 
        if( find )
            continue;
 
        qtd++;
        ans[qtd] = v[i] - ans[1];
 
        nxt[1]++;
 
        if( ans[qtd] <= 0 || qtd > n )
            return false;
    }
 
    for(int i = 1 ; i <= n ; i++)
        printf("%d ",ans[i]);
 
    return true;
}
 
int main()
{
    cin >> n;
 
    for(int i = 1 ; 2*i <= n*(n - 1) ; i++)
        cin >> v[i];
 
    sort( v + 1 , v + n + 1 );
 
    for(int i = 3 ; i <= n ; i++)
    {
        int value = v[1] + v[2] - v[i];
 
        if( value%2 == 1 || value <= 0 )
            continue;
 
        if( solve(value/2) )
            return 0;
    }
}