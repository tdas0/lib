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
ll modpow(ll b, ll e ,ll mod) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}

struct suffix_automaton{
	enum{alpha  = 26 , first = 'a'};
	struct node{
		int len, link;
		vi next;
		node(int x , int y , int v){
			len = x , link = y;
			next = vi(alpha);
			rep(i,0,alpha) next[i] = v;
		}

	};
	ll substrings = 0; int last = 0 ;
	vector<node> st; 
	suffix_automaton(int v = 0){st.push_back(node(0,-1,0));}
	void extend(char c){
		c -= first;
		int cur = sz(st) , p,q;
		st.push_back(node(st[last].len + 1,-1,0));
	    for (p=last; p!=-1 && !st[p].next[c]; p=st[p].link) st[p].next[c] = cur;				
		if(p == -1) st[cur].link = 0 ,substrings += st[cur].len;
		else{
			q = st[p].next[c];
			if(st[p].len + 1 == st[q].len){
				st[cur].link = q;
				substrings += st[cur].len - st[q].len;
			}
			else{
				int clone = sz(st);
				st.push_back(node(st[p].len+1,st[q].link,0));
				st.back().next = st[q].next;
	            substrings += st[clone].len - st[st[clone].link].len;
	            for (; p!=-1 && st[p].next[c]==q; p=st[p].link)
	                st[p].next[c] = clone;
	            substrings -= st[q].len - st[st[q].link].len;
	            st[q].link = st[cur].link = clone;
	            substrings += st[q].len - st[st[q].link].len + st[cur].len - st[st[cur].link].len;
			}
		} 
		last = cur;
	}
	vi terminal(){
		int p = last; vi t;
		while(p >= 0){
			t.push_back(p), p = st[p].link;
		}
		return t;
	}
	bool find(const string &s){
		int p = 0;
		rep(j,0,sz(s)){
			if(!st[p].next[s[j]-first]) return false;
			p = st[p].next[s[j]-first];
		}
		return true;
	}
};

int32_t main(){
	string s;
	suffix_automaton sa;
	cin >> s;
	rep(i,0,sz(s)){
		sa.extend(s[i]);
		cout << sa.substrings << "\n";
	}
}