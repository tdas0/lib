#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define int long long
#define pb push_back
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
ll mod;

template<class T, int N> struct Matrix {
	typedef Matrix M;
	array<array<T, N>, N> d{};
	M operator*(const M& m) const {
		M a;
		rep(i,0,N) rep(j,0,N)
			rep(k,0,N){
				a.d[i][j] += d[i][k]*m.d[k][j];
				a.d[i][j] %= mod;
			}
		return a;
	}
	vector<T> operator*(const vector<T>& vec) const {
		vector<T> ret(N);
		rep(i,0,N) rep(j,0,N){
			ret[i] += d[i][j] * vec[j];
			ret[i] %= mod;
		}
		return ret;
	}
	M operator^(ll p) const {
		assert(p >= 0);
		M a, b(*this);
		rep(i,0,N) a.d[i][i] = 1;
		while (p) {
			if (p&1) a = a*b;
			b = b*b;
			p >>= 1;
		}
		return a;
	}
};
int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	int q;
	cin>>q;
	while(q--){
		int P, A,B,C,K, N;
		int A2,B2,C2,K2, N2;
		cin>>P>>A>>B>>C>>K>>N;
		cin>>A2>>B2>>C2>>K2>>N2;
		mod = P;
		Matrix<ll, 4> base;
		base.d[0][0]=0,base.d[0][1]=K,base.d[0][2]=1,base.d[0][3]=0;
		base.d[1][0]=1,base.d[1][1]=0,base.d[1][2]=K,base.d[1][3]=0;
		base.d[2][0]=1,base.d[2][1]=0,base.d[2][2]=0,base.d[2][3]=1;
		base.d[3][0]=0,base.d[3][1]=1,base.d[3][2]=0,base.d[3][3]=0;
		if(N >= 2)base=(base^(N-2));

		Matrix<ll, 4> base2;
		base2.d[0][0]=0,base2.d[0][1]=K2,base2.d[0][2]=1,base2.d[0][3]=0;
		base2.d[1][0]=1,base2.d[1][1]=0,base2.d[1][2]=K2,base2.d[1][3]=0;
		base2.d[2][0]=1,base2.d[2][1]=0,base2.d[2][2]=0,base2.d[2][3]=1;
		base2.d[3][0]=0,base2.d[3][1]=1,base2.d[3][2]=0,base2.d[3][3]=0;
		if(N2 >= 2)base2=(base2^(N2-2));

		ll xcord;
		cin>>xcord;
		int ans=-1;
		int qtd=0;
		vector<ll> caras;
		for(int h=0;h<P;h++){
			Matrix <ll, 4> X, Y;
			int F2 = B + C;
			int G2 = K*A + h;
			int H2 = A + K*B;
			X.d[0][0] = F2%mod, X.d[0][1] = G2%mod, X.d[0][2] = H2%mod, X.d[0][3] = C%mod;

			int F22 = B2 + C2;
			int G22 = K2*A2 + h;
			int H22 = A2 + K2*B2;
			Y.d[0][0] = F22%mod, Y.d[0][1] = G22%mod, Y.d[0][2] = H22%mod, Y.d[0][3] = C2%mod;

			int myX = A, myY = A2;
			if(N >= 2){
				X = (X*base);
				myX = X.d[0][0];
			}
			if(N2 >= 2){
				Y = (Y*base2);
				myY = Y.d[0][0];
			}

			// cout<<h<<" "<<myX<<" "<<myY<<"\n";
			if(myX == xcord){
				caras.pb(myY);
			}
		}
		sort(all(caras));
		caras.erase(unique(all(caras)),caras.end());
		if(sz(caras) !=1) cout<<"UNKNOWN\n";
		else cout<<caras[0]<<"\n";
	}

}

