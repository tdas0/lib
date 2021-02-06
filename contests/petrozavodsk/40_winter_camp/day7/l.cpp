#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
using namespace std;

// #define int long long
typedef long long ll;
typedef pair<int, int> pii;

#define N 200050

double m, g, b1, b2, t1, hf;
double f(double b, double k1, double k2, double t){
	double e = exp( (-b*t)/m);
	double y = (k1*m*e)/b + (g*t*m)/b + k2;
	return y;
}

double F(double k1, double k2, double k1_, double k2_, double t){
	if ( t <= t1) return f(b1, k1, k2, t);

	double t2 = t - t1;
	return f(b2, k1_, k2_, t);
}
double y_linha(double t, double k1){
	return (m*g)/b1 - k1*exp(-(b1*t)/m);
}
int32_t main(){
	ios::sync_with_stdio(false); cin.tie();
	int a, B, c, d, e;
	cin>>a>>B>>c>>d>>e;
	m = a, b1 = B, b2 = c, t1 = d, hf = e, g = 9.81;

	double k1 = (m*g)/b1;
	double k2 = -1.0 * (k1*m/b1);

	double k1_ = ((g*m)/b2 - y_linha(t1, k1))/(exp((-b2*t1)/m));
	double k2_ = f(b1, k1, k2, t1) - (m*g*t1)/b2 - (k1_*m*exp((-b2*t1)/m))/(b2);

	cout<<setprecision(10)<<fixed;
	int q;
	cin>>q;
	while(q--){
		int t;
		cin>>t;

		cout<<min(hf, F(k1, k2, k1_, k2_, 1.0*t))<<"\n";
	}
	double ini = 0, fim = (1e7), mid, best;
	for(int it = 0; it < 1000; it++){
		mid = (ini + fim)/2;
		if(F(k1, k2, k1_, k2_, mid) >= hf){
			fim = mid;
		}
		else ini = mid;
	}
	cout<<mid<<"\n";
}
