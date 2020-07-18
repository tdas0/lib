#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ff first
#define ss second
#define endl '\n'
using namespace std;
typedef pair<int,int> pii;
int k;

vector<vector<int>>dp[51][2];
const int N = 5005;
char mat[N][N];
int n,m;
const int inf = 1e7;
inline bool ok(int l,int c){
	return l>=1 and l<=n and c>=1 and c<=m and mat[l][c]!='#';
}
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};

struct dado{
 int i,j,k,f,dist;
 dado(){

 }
 dado(int a,int b,int c,int d,int e){
 	 i =a;
 	 j = b;
 	 k = c;
 	 f = d;
 	 dist = e;
 }
};


int solve(int inii,int inij){
	queue<dado> pq;
	dp[0][0][inii][inij] = 0;
	pq.push(dado(inii,inij,0,0,0));

	while(!pq.empty()){
		dado cur = pq.front();
		pq.pop();
		int dist = dp[cur.k][cur.f][cur.i][cur.j];
		

		for(int q=0;q<4;q++){
			int l = cur.i + dx[q];
			int c = cur.j + dy[q];
			if(ok(l,c)){
			int f = mat[l][c]=='D' ? 1 : 0;
				if(f){

				if(cur.f){
					if(dp[cur.k][0][l][c] > dist + 1){
						dp[cur.k][0][l][c] = dist + 1;
						pq.push(dado(l,c,cur.k,0,dist + 1));
					}
				}else{
					if(cur.k + 1<=k and dp[cur.k+1][1][cur.i][cur.j] > dist + 1){
						dp[cur.k+1][1][cur.i][cur.j] = dist + 1;
						pq.push(dado(cur.i,cur.j,cur.k+1,1,dist + 1));
					}
				}

				}else{
					if(dp[cur.k][0][l][c] > dist + 1){
						dp[cur.k][0][l][c] = dist + 1;
						pq.push(dado(l,c,cur.k,0,dist+1));
					}

				}

			}

		}

		if(cur.k > 0 ){
			if(dp[cur.k-1][cur.f][cur.i][cur.j] > dist + 1){
				dp[cur.k-1][cur.f][cur.i][cur.j] = dist + 1;
				pq.push(dado(cur.i,cur.j,cur.k - 1,cur.f,dist+1));
			}
		}

	}

	int best = inf;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){

			if(mat[i][j]=='B'){

				for(int l=0;l<=k;l++){
					for(int f=0;f<2;f++)best = min(best,dp[l][f][i][j]);
				}

			}

		}
	}
	return best;
}
struct dado2{
 int i,j,k,f,dist;
 dado2(){}
 dado2(int a,int b,int c,int d,int e){
 	 i =a;
 	 j = b;
 	 k = c;
 	 f = d;
 	 dist = e;
 }
};
bool operator<(const dado2& a,const dado2&b){
	return a.dist > b.dist;
}

vector<vector<int> > dp2[2][2];
 
int solve2(int inii,int inij){
	priority_queue<dado2> pq;
	dp2[0][0][inii][inij] = 0;
	pq.push(dado2(inii,inij,0,0,0));
 
	while(!pq.empty()){
		dado2 cur = pq.top();
		pq.pop();
		int dist = dp2[cur.k][cur.f][cur.i][cur.j];
		if(cur.f){
			if(dp2[cur.k-1][0][cur.i][cur.j] > dist + 1){
				dp2[cur.k-1][0][cur.i][cur.j] = dist + 1;
				pq.push(dado2(cur.i,cur.j,cur.k - 1 ,0,dist+1));
			}
		}
 
		int f2 = mat[cur.i][cur.j]=='D' ? 1 : 0;
		for(int q=0;q<4;q++){
			int l = cur.i + dx[q];
			int c = cur.j + dy[q];
			int f = mat[l][c]=='D' ? 1 : 0;
			if(ok(l,c)){
				if(f){
 
				if(cur.k+f<=k and dp2[cur.k+f][f2][l][c] > dist + 2){
					dp2[cur.k + f][f2][l][c] = dist + 2;
					pq.push(dado2(l,c,cur.k + f,f2,dist+2));
				}
 
				}else{
					if(dp2[cur.k][f2][l][c] > dist + 1){
						dp2[cur.k][f2][l][c] = dist + 1;
						pq.push(dado2(l,c,cur.k,f2,dist+1));
					}
 
				}
 
			}
 
		}
 
	}
 
	int best = inf;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
 
			if(mat[i][j]=='B'){
 
				for(int l=0;l<=k;l++){
					for(int f=0;f<2;f++){
						best = min(best,dp2[l][f][i][j]);
					}
				}
 
			}
 
		}
	}
	return best;
}


int r,c;
void QUERY(){
	//scanf("%d%d%d",&r,&c,&k);
	cin >> r>> c >> k;
	n = r,m=c;
	for(int i=0;i<=k;i++){
		if(k>1){
			
			for(int j=0;j<2;j++)
				dp[i][j] = (vector<vector<int> >(r+1,vector<int>(c+1,inf)));
			
		}else{
			for(int j=0;j<2;j++){
				dp2[i][j] = (vector<vector<int>>(r+1,vector<int>(c+1,inf)));
			}
		}
	}

	pii ini;
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			cin >> mat[i][j];
			if(mat[i][j]=='A')ini = pii(i,j);
		}
	}


	
	int res =inf;
	if(k>1)res = solve(ini.ff,ini.ss);
	else res = solve2(ini.ff,ini.ss);
	if(res>=inf)cout << "HAHAHUHU" << endl;
	else cout << res << endl;

	for(int i=0;i<=k;i++){
		if(k>1){
			for(int j=0;j<2;j++)dp[i][j].clear();
		}
		else{
			for(int j=0;j<2;j++){
				dp2[i][j].clear();
			}
		}
	}
}

int main(){
	fastio;
	int t;
	cin >> t;
	while(t--){
		QUERY();
	}

}