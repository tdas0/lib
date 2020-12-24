#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
using namespace std;
#define int long long
typedef long long ll;
typedef pair<int, int> pii;
#define N 300050

// {S, P, O}
pair<int, pii > w[N];
int n, d;
bool cmp(pair<int, pii> A, pair<int, pii> B){
	int Pi = A.s.f, Si = A.f,Oi = A.s.s;
	int Sj = B.f, Oj = B.s.s, Pj = B.s.f;
	// return Si*(Oi + Pi*d) < Sj*(Oj + Pj*d);
	return Si*(Pi) < Sj*Pj;
}
bool check(double x){
	double peso = x;
	double deep = 0;
	for(int i = 1; i <= n; i++){
		double Si = w[i].f, Pi = w[i].s.f, Oi = w[i].s.s;
		double len = (Si*Oi - peso)/(Si*Pi);
		if(len >= d) return 1;
	}
	for(int i = 1; i <= n; i++){
		double Si = w[i].f, Pi = w[i].s.f, Oi = w[i].s.s;
		double len = (Si*Oi - peso)/(Si*Pi);
		if(len > 0.0){
			deep += len;
			peso += len*Si*Pi;
		}
	}
	if(deep >= d) return 1;
	return false;
}
int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>d>>n;
	for(int i = 1; i <= n; i++){
		cin>>w[i].f>>w[i].s.f>>w[i].s.s;
	}
	sort(w + 1, w + n + 1, cmp);
	double ini = 0, fim = (1e7),mid,best;
	for(int cnt=0;cnt<=200;cnt++){
		mid = (ini + fim)/2;
		if(check(mid)){
			ini = mid;
			best=mid;
		}
		else fim=mid;
	}
	cout<<setprecision(10)<<fixed;
	cout<<best<<"\n";
}
