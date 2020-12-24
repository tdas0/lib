#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
typedef vector<int> vi;
#define endl '\n'
#define pb push_back
const int L = 105;
struct kmp{
	vector<int> b, pos , match;
	string s, p;
	//A = texto, B = padrao
	void build(string A, string B){
		s = A, p = B;
		int n = sz(s), m = sz(p);
		match.resize(n + 1);
		b.resize(m + 1);
		b[0] = -1;
		for(int i = 0, j = -1; i < m; i++) {
			while(j >= 0 and p[i] != p[j]) j = b[j];
			j ++;
			b[i + 1] = j;
		}

		//achar posicoes onde o padrao aparece
		for(int i = 0, j = 0; i < n; i++){
			while(j >= 0 and s[i] != p[j]) j = b[j];
			j ++;
			if(j == m){ 
				pos.push_back(i - j + 1);
				match[i]++;
			}
		}
	}
	void clear(){
		s="", p="";
		pos.clear();
		b.clear();
		match.clear();
	}
} KMP[L];

const int N = 5e4 + 10;
ll cnt[N][L],cnt2[N][L];
ll acu[N],acu2[N];

int32_t main(){
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n,m,k;
	cin >> n >> m >> k;
	string S,T;
	cin >> S;
	cin >> T;

	for(int tam = 1;tam<=sz(T);tam ++ ){
		string cur = T.substr(0,tam);
		KMP[tam].build(S,cur);
	}

	for(int i=0;i<n;i++){
		if(i){
			acu[i] = acu[i-1];
			for(int j=0;j<=sz(T);j++){
				cnt[i][j] = cnt[i-1][j];
			}
		}
		for(int j=0;j<=sz(T);j++){
			if(j>0){
				if(j!=m)cnt[i][j] += KMP[j].match[i];
				else if(KMP[j].match[i]){
					acu[i]+=-i + 1;
					cnt[i][j]++;
				}
			}else cnt[i][j]++;

		}
	}

	for(int tam = 1;tam<=sz(T);tam ++ ){
		string cur = T.substr(sz(T) - tam,tam);
		KMP[tam].clear();
		KMP[tam].build(S,cur);
	}
	for(int i=n-1;i>=0;i--){
		for(int j=0; j <= sz(T) ;j++){
			cnt2[i][j] = cnt2[i+1][j];
			acu2[i] = acu2[i+1];
			if(j>0){
				if(j!=m){
					if(i + j - 1 < n)cnt2[i][j]+=KMP[j].match[i + j - 1];
				}else{
					if(i + j - 1 < n and KMP[j].match[i + j - 1]){
						acu2[i]+=i+1;
						cnt2[i][j]++;
					}
				}
			}else cnt2[i][j]++;
		}
	}

	while(k--){
		ll ans=0;
		int L,R;
		cin >> L >> R;
		L--;R--;
		rep(j,0,sz(T)+1){
			if(j == 0){
				
				ans += 1ll * (n-R)*(cnt[L][m]*L + acu[L]);
			
			}else if(j == m){
			
				ans+= 1ll * (acu2[R] - R * cnt2[R][m]) * (L+1);

			}else{ 
			
				ans+=1ll*cnt[L][j]*cnt2[R][m - j];
			
			}
		}
		cout << ans << endl;
	}

}
