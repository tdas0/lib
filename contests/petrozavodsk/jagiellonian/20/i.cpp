#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
#include <climits>

using namespace std;

#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x) , end(x)
#define sz(x) (int)(x).size()
#define pb push_back

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
typedef vector<int> vi;

ll modpow(ll b, ll e ,ll mod){
    ll ans = 1;
    for (; e; b = b * b % mod, e /= 2)
        if (e & 1) ans = ans * b % mod;
    return ans;
}

const int BASE_DIGITS = 9;
const int BASE = 1000000000;

struct BigInt {
    int sign;
    vector<int> a;

    // -------------------- Constructors -------------------- 
    // Default constructor.
    BigInt() : sign(1) {}

    // Constructor from long long.
    BigInt(long long v) {
        *this = v;
    }
    BigInt& operator = (long long v) {
        sign = 1;
        if (v < 0) {
            sign = -1;
            v = -v;
        }
        a.clear();
        for (; v > 0; v = v / BASE)
            a.push_back(v % BASE);
        return *this;
    }

    // Initialize from string.
    BigInt(const string& s) {
        read(s);
    }

    // -------------------- Input / Output --------------------
    void read(const string& s) {
        sign = 1;
        a.clear();
        int pos = 0;
        while (pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-')
                sign = -sign;
            ++pos;
        }
        for (int i = s.size() - 1; i >= pos; i -= BASE_DIGITS) {
            int x = 0;
            for (int j = max(pos, i - BASE_DIGITS + 1); j <= i; j++)
                x = x * 10 + s[j] - '0';
            a.push_back(x);
        }
        trim();
    }
    friend istream& operator>>(istream &stream, BigInt &v) {
        string s;
        stream >> s;
        v.read(s);
        return stream;
    }

    friend ostream& operator<<(ostream &stream, const BigInt &v) {
        if (v.sign == -1 && !v.isZero())
            stream << '-';
        stream << (v.a.empty() ? 0 : v.a.back());
        for (int i = (int) v.a.size() - 2; i >= 0; --i)
            stream << setw(BASE_DIGITS) << setfill('0') << v.a[i];
        return stream;
    }

    // -------------------- Comparison --------------------
    bool operator<(const BigInt &v) const {
        if (sign != v.sign)
            return sign < v.sign;
        if (a.size() != v.a.size())
            return a.size() * sign < v.a.size() * v.sign;
        for (int i = ((int) a.size()) - 1; i >= 0; i--)
            if (a[i] != v.a[i])
                return a[i] * sign < v.a[i] * sign;
        return false;
    }

    bool operator>(const BigInt &v) const {
        return v < *this;
    }
    bool operator<=(const BigInt &v) const {
        return !(v < *this);
    }
    bool operator>=(const BigInt &v) const {
        return !(*this < v);
    }
    bool operator==(const BigInt &v) const {
        return !(*this < v) && !(v < *this);
    }
    bool operator!=(const BigInt &v) const {
        return *this < v || v < *this;
    }

    // Returns:
    // 0 if |x| == |y|
    // -1 if |x| < |y|
    // 1 if |x| > |y|
    friend int __compare_abs(const BigInt& x, const BigInt& y) {
        if (x.a.size() != y.a.size()) {
            return x.a.size() < y.a.size() ? -1 : 1;
        }

        for (int i = ((int) x.a.size()) - 1; i >= 0; --i) {
            if (x.a[i] != y.a[i]) {
                return x.a[i] < y.a[i] ? -1 : 1;
            }
        }
        return 0;
    }

    // -------------------- Unary operator - and operators +- --------------------
    BigInt operator-() const {
        BigInt res = *this;
        if (isZero()) return res;

        res.sign = -sign;
        return res;
    }

    // Note: sign ignored.
    void __internal_add(const BigInt& v) {
        if (a.size() < v.a.size()) {
            a.resize(v.a.size(), 0);
        }
        for (int i = 0, carry = 0; i < (int) max(a.size(), v.a.size()) || carry; ++i) {
            if (i == (int) a.size()) a.push_back(0);

            a[i] += carry + (i < (int) v.a.size() ? v.a[i] : 0);
            carry = a[i] >= BASE;
            if (carry) a[i] -= BASE;
        }
    }

    // Note: sign ignored.
    void __internal_sub(const BigInt& v) {
        for (int i = 0, carry = 0; i < (int) v.a.size() || carry; ++i) {
            a[i] -= carry + (i < (int) v.a.size() ? v.a[i] : 0);
            carry = a[i] < 0;
            if (carry) a[i] += BASE;
        }
        this->trim();
    }

    BigInt operator += (const BigInt& v) {
        if (sign == v.sign) {
            __internal_add(v);
        } else {
            if (__compare_abs(*this, v) >= 0) {
                __internal_sub(v);
            } else {
                BigInt vv = v;
                swap(*this, vv);
                __internal_sub(vv);
            }
        }
        return *this;
    }

    BigInt operator -= (const BigInt& v) {
        if (sign == v.sign) {
            if (__compare_abs(*this, v) >= 0) {
                __internal_sub(v);
            } else {
                BigInt vv = v;
                swap(*this, vv);
                __internal_sub(vv);
                this->sign = -this->sign;
            }
        } else {
            __internal_add(v);
        }
        return *this;
    }

       BigInt abs() const {
        BigInt res = *this;
        res.sign *= res.sign;
        return res;
    }
    void trim() {
        while (!a.empty() && !a.back())
            a.pop_back();
        if (a.empty())
            sign = 1;
    }
    bool isZero() const {
        return a.empty() || (a.size() == 1 && !a[0]);
    }
};
vi recover(BigInt v){
    vi ans;
    if(sz(v.a) == 0 || v.a.back() == 0){
        ans.push_back(0);
    }
    else{
        vi p;
        while(v.a.back() > 0){
            p.push_back(v.a.back() % 10);
            v.a.back() /= 10;
        }
        reverse(all(p));
        for(auto w : p)ans.push_back(w);
    }
    for(int i = (int) v.a.size() -2 ; i >= 0 ; --i){
        vi p ;
        while(sz(p) != BASE_DIGITS){
            p.push_back(v.a[i] % 10);
            v.a[i] /= 10;
        }
        reverse(all(p));
        // cout << sz(p) << endl;
        for(auto w : p) ans.push_back(w);
    }
    return ans;
}

bool palindrome(BigInt U){
	vector<int> X = recover(U);
	int st=0;
	for(int i = 0; i < sz(X); i++){
		if(X[i] != 0){
			st=i;
			break;
		}
	}
	int en = sz(X)-1;
	while(st<=en){
		if(X[st]!=X[en])return false;
		st++,en--;
	}
	return true;
}
vector<BigInt> ans;
void vi2big(vector<int> w, BigInt &v){
	string curr = "";
	for(auto x: w) curr.pb(x+'0');
	v.read(curr);
}
void solve(BigInt X){
	// cout<<"SOLVE "<<X<<"\n";
	vector<int> Y = recover(X);
	int can =0;
	// cout<<"PORRA "<<X<<"\n";
	vector<int> aux;
	for(int i=0;i<sz(Y); i++){
		if(Y[i]!=0)can=1;
		if(can==1)aux.pb(Y[i]);
	}
	Y=aux;
	if(palindrome(X)){
		ans.pb(X);
		return;
	}
	int mid= ((sz(Y))/2);
	for(int i = mid-1;i>=1; i--){
		if(Y[i] != 0){
			vector<int> tmp;
			for(int j = 0; j < i; j++){
				tmp.pb(Y[j]);
			}
			vector<int> cara;
			tmp.pb(Y[i]-1);
			cara = tmp;
			int resta = sz(Y) - 2*sz(tmp);
			while(resta--){
				cara.pb(0);
			}
			reverse(all(tmp));
			for(auto x: tmp) cara.pb(x);
			BigInt A(sz(Y)), PAL(sz(cara));
			vi2big(Y, A);
			vi2big(cara, PAL);
			// cout<<A<<" "<<PAL<<" = ";
			A -= PAL;
			ans.pb(PAL);
			// cout<<A<<"\n";
			solve(A);
			return;
		}
	}
	vector<int>cara;
	// cout<<"OI\n";
	BigInt A(sz(Y));
	vi2big(Y, A);

	if(Y[0] > 1){
		vector<int>tmp;
			tmp.pb(Y[0]-1);
			cara = tmp;
			int resta = sz(Y) - 2*sz(tmp);
			while(resta--){
				cara.pb(0);
			}
			reverse(all(tmp));
			for(auto x: tmp) cara.pb(x);
	}
	else{
		string curr;
		for(int i=0;i<sz(Y);i++){
			if(i==0 or i==sz(Y)-1) curr.pb('1');
			else curr.pb('0');
		}
		BigInt H(sz(curr));
		H.read(curr);
		if(A >= H){
			A -= H;
			ans.pb(H);
			solve(A);
			return;
		}
		else{
			curr.clear();
			for(int i = 0; i < sz(Y)-1;i++){
				curr.pb('9');
			}
			BigInt H2(sz(curr));
			H2.read(curr);
			A -= H2;
			ans.pb(H2);
			solve(A);
			return ;
		}
	}
	BigInt PAL(sz(cara));
	vi2big(cara, PAL);
	// cout<<A<<" "<<PAL<<" = ";
	A -= PAL;
	ans.pb(PAL);
	// cout<<A<<"\n";

	solve(A);
	return;
}
int32_t main(){
   int q;
   cin>>q;
   while(q--){
   	ans.clear();
		string s;
		cin>>s;
		BigInt X(sz(s));
		X.read(s);
		solve(X);
		assert(sz(ans) <= 25);
		cout<<sz(ans)<<"\n";
		for(auto w: ans) cout<<w<<"\n";
   }

}

/* clever stuff:
    * int overflow, array bounds
    * special cases (n=1?)
    * do smth instead of nothing and STAY ORGANIZED
    * Keep it simple stupid
    * WRITE STUFF DOWN
    * math -> gcd / lcm / divisors? 
*/

