#include <bits/stdc++.h>
using namespace std;
#define int long long
#define sz(x) (int)(x).size()

int n, d, C;
int choose[51][51];

// double solve(int i, int x, int y, int z){
// 	cout<<i<<" "<<x<<" "<<y<<" "<<z<<"\n";
// 	if((!x and !z)) return (double)(i);
// 	if((!y and !z)) return (double)(i);
// 	if(i>=600) return 0.0;
// 	double ans = 0;
// 	if(vis[i][x][y][z]) return dp[i][x][y][z];
// 	vis[i][x][y][z]=1;
// 	for(int a = 0; a <= min(d, x); a++){
// 		for(int  b = 0; b <= min(d,y); b++){
// 			for(int c = 0; a + b + c <=d; c++){
// 				if(c>z or (a+b+c==0))continue;
// 				// if(a+b+c <= d and n-x-y-z)
// 				if(!(n-x-y-z >= 0 and d-a-b-c>=0))continue;
// 				if(d - (n-x-y-z) <= a+b+c and a+b+c<=d){
// 					double P = (choose[z][c] * choose[x][a] * choose[y][b] * choose[n-x-y-z][d-a-b-c]);
// 					P /= (double)choose[n][d];
// 					ans += P*(solve(i + 1, x - a, y - b, z - c));
// 				}
// 			}
// 		}
// 	}

// 	return dp[i][x][y][z] = ans;
// }
double dp[20][20][20];
bool vis[20][20][20];
double solve(int x, int y, int z){
	if(!z and (!x or !y)) return 0.0;
	double ans = 1.0;
	if(vis[x][y][z]) return dp[x][y][z];
	vis[x][y][z]=1;
	for(int a = 0; a <= min(x, d); a++){
		for(int b = 0; b <= min(y,d); b++){
			for(int c = 0; c <= min(z, d); c++){
				if(a + b + c > d or (a+b+c) == 0) continue;
				double P = choose[z][c] * choose[x][a] * choose[y][b] * choose[n-x-y-z][d-a-b-c];
				P /= (double)choose[n][d];
				ans += P * solve(x-a,y-b,z-c);
			}
		}
	}
	double p2 = (double)choose[n-x-y-z][d]/(double)choose[n][d];
	ans /= (1.00 - p2);
	return dp[x][y][z] = ans;
}
int32_t main(){
	ios::sync_with_stdio(false), cin.tie(0);
	cin>>n>>d>>C;
	for(int i = 0; i < 51; i++){
		for(int j = 0; j < 51; j++){
			if(j > i) choose[i][j] = 0;
			else if(!j) choose[i][j] = 1;
			else choose[i][j] = (choose[i-1][j] + choose[i-1][j-1]);
			//cout<<i<<" "<<j<<" "<<choose[i][j]<<"\n";
		}
	}
	int equal = 0;
	vector<int> A(100), B(100);
	set<int> l;
	int tamx = C, tamy = 0;
	for(int i = 1; i <= C; i++){
		cin>>A[i];
		l.insert(A[i]);
	}
	for(int i = 1; i <= C; i++){
		cin>>B[i];
		if(l.count(B[i])) equal ++, tamx--;
		else tamy ++;
	}
	cout<<setprecision(10)<<fixed;
	cout<<solve(tamx, tamy, equal)<<"\n";
}