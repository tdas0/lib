/**
 * Author: Tiago Domingos
 * Description: Matrix class
 * Status:tested
 * !!! If get TLE, try to change vector<vector<T>> to an array
 * ~ 4 x faster on https://codeforces.com/gym/102644/problem/H
 */
template<class T>
struct Mat{
	int n, m; vector< vector<T> > d;
	Mat(int n , int m): n(n) , m(m){
		d.assign(n , vector<T>(m));
	}
	Mat() : Mat(0,0) {}
	Mat(const vector<vector<T>>&_d) : n(sz(_d)) , m(sz(_d[0])) {d=_d;}
	Mat & operator+=(const Mat&a){
		rep(i,0,n) rep(j,0,m) d[i][j] += a.d[i][j];
		return *this;
	}
	Mat & operator-=(const Mat&a){
		rep(i,0,n) rep(j,0,m) d[i][j] -= a.d[i][j];
		return *this;
	}
	Mat  operator*(const Mat&a){ // m == a.n
		Mat x(n,a.m);
		rep(i,0,n) rep(j,0,m) rep(k,0,a.m)
			x.d[i][k] += d[i][j] * a.d[j][k];
		return x;
	}
	Mat operator+(const Mat&a){
		return Mat(*this)+= a;
	}
	Mat operator-(const Mat&a){
		return Mat(*this)-= a;
	}
	Mat & operator*=(const Mat&a){
		return *this = (*this)*a;
	}
	Mat & operator^=(const ll& x){
		return *this = pow(*this , x);
	}
	Mat operator^(const ll &x){
		return Mat(*this)^= x;
	}
	friend Mat pow(Mat a, ll p){
		Mat res(a.n,a.m); rep(i,0,a.n) res.d[i][i] = 1;
		for(; p ; p/=2 , a *= a) if(p&1) res *= a;
		return res;
	}
 };
