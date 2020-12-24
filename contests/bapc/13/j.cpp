#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define N 110
char mat[N][N];
int n, m, dx[4]={1,-1,0,0}, dy[4]={0,0,1,-1};
int dist[N][N][3];
void bfs(vector<pii> caras, int flag){
	deque<pii> fila;
	vector<vector<int> > vis(n+1);
	for(int i=0;i<=n;i++) vis[i].resize(m+1);
	for(int i=0;i<=n;i++)
		for(int j=0;j<=m;j++)
			vis[i][j]=-1;

	for(auto p:caras){
		int x=p.f, y=p.s;
		fila.push_back({x, y});
		int cc = (mat[x][y] == '#'?1:0);
		vis[x][y]=cc;
	}
	while(!fila.empty()){
		int x=fila.front().f, y=fila.front().s;
		fila.pop_front();
		for(int i = 0; i < 4;i++){
			int a =x+dx[i], b=y+dy[i];
			if(a<=0 or b<=0 or a>n or b>m or mat[a][b] =='*' or vis[a][b] != -1) continue;
			int cc = (mat[a][b] == '#'?1:0);
			vis[a][b]=vis[x][y]+cc;
			if(cc)fila.push_back({a, b});
			else fila.push_front({a, b});
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			dist[i][j][flag]= vis[i][j];
}
int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	int q;
	cin>>q;
	while(q--){
		cin>>n>>m;
		pii L={-1,-1}, R={-1,-1};
		for(int i =1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>mat[i][j];
				if(mat[i][j] == '$'){
					if(L.f == -1) L = {i,j};
					else R ={i,j};
				}
			}
		}
		bfs({L}, 0);
		bfs({R}, 1);
		vector<pii> borda;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if( (i==1 or i==n or j==1 or j==m) and mat[i][j] != '*')
					borda.pb({i, j});
		
		int dmin = 2000000000;
		bfs(borda, 2);
		for(int i =1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(mat[i][j] == '*' or dist[i][j][0] == -1 or dist[i][j][1] == -1 or dist[i][j][2] == -1) continue;
				// cout<<"dd "<<i<<" "<<j<<" = "<<dist[i][j][0]<<"\n";
				int cost = dist[i][j][0]+dist[i][j][1]+dist[i][j][2];
				if(mat[i][j] == '#') cost -= 2;
				dmin=min(dmin, cost);
			}
		}
		cout<<dmin<<"\n";
	}
}
