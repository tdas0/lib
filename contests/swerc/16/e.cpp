#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) (x).begin() , (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<int> vi;
const ll mod = 1000003;
ll dp[3003][55][2][2][2];
bool vis[3003][55][2][2][2];
int A , B ;
map<char,int> lf;
struct AhoCorasick{
	enum{alpha = 256 , first = 0}; 
	struct Node{
		int back, next[alpha] , start = - 1, end = -1 , nmatches = 0;
		Node(int v){memset(next ,v, sizeof(next));}
	};
	vector<Node> N;
	vector<int> backp;
	void insert(string &s , int j){
		int n = 0;
		for(int i = 0 ; i < s.size() ; i ++){
			char c = s[i];
			int &m = N[n].next[c-first];
			if(m == -1){n = m = sz(N) ; N.push_back(-1);}
			else n = m;
		}
		if(N[n].end == -1) N[n].start = j;
		backp.push_back(N[n].end);
		N[n].end = j;
		N[n].nmatches++;
	}
	AhoCorasick(vector<string> &pat){
		N.push_back(-1);
		rep(i,0,sz(pat)) insert(pat[i] , i);
		N[0].back = sz(N);
		N.push_back(0);
		queue<int> q;
		for(q.push(0) ; !q.empty() ; q.pop()){
			int n = q.front() , prev = N[n].back;
			rep(i,0,alpha){
				int &ed = N[n].next[i] , y = N[prev].next[i];
				if(ed == -1) ed = y;
				else{
					N[ed].back = y;
					(N[ed].end == -1 ? N[ed].end : backp[N[ed].start]) = N[y].end;
					N[ed].nmatches += N[y].nmatches;
					q.push(ed);
				}
			}
		}
	}
	ll solve(int x , int y , int z , int w , int k){
		if(y > B){
			return 0ll;
		}
		if(vis[x][y][z][w][k]) return dp[x][y][z][w][k];
		vis[x][y][z][w][k] = 1;
		if(y >= A && y <= B && z && w && k) dp[x][y][z][w][k] = 1;
		for(char i = 'a' ; i <= 'z' ; i ++){
			if(!N[N[x].next[i]].nmatches){
				dp[x][y][z][w][k] = (dp[x][y][z][w][k] + solve(N[x].next[i] , y + 1 ,z | 1, w , k ))%mod;
			}
		}
		for(char i = 'A' ; i <= 'Z' ; i ++){
			if(!N[N[x].next[i - 'A' + 'a']].nmatches){
				dp[x][y][z][w][k] = (dp[x][y][z][w][k] + solve(N[x].next[i - 'A' + 'a'] , y + 1 , z , w|1 , k) )%mod;
			}
		}
		for(char i = '0' ; i <= '9' ; i++){
			if(lf.count(i)){
				if(!N[N[x].next[lf[i]]].nmatches){
					dp[x][y][z][w][k] = (dp[x][y][z][w][k] + solve(N[x].next[lf[i]] , y + 1 , z , w , k|1)) %mod;
				}
			}
			else{
				if(!N[N[x].next[i]].nmatches){
					dp[x][y][z][w][k] = (dp[x][y][z][w][k] + solve(N[x].next[i] , y + 1 ,z, w , k|1))%mod;					
				}
			}
		}
		return dp[x][y][z][w][k];
	}
};
int N;
int32_t main(){
	cin >> A >> B >> N;
	vector<string> v(N);
	lf['0'] = 'o';
	lf['1'] = 'i';
	lf['3'] = 'e';
	lf['5'] = 's';
	lf['7'] = 't';
	rep(i,0,N){
		cin >> v[i];
		rep(j,0,sz(v[i])){
			if(lf.count(v[i][j])) v[i][j] = lf[v[i][j]];
			if(v[i][j] >= 'A' && v[i][j] <= 'Z') v[i][j] = v[i][j] - 'A' + 'a';
		}
	}
	AhoCorasick aho(v);
	ll ans = aho.solve(0,0,0,0,0);
	cout << ans << endl;
}	