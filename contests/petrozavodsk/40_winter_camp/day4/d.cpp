#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
typedef long long ll;

struct insect{
	int type, level;
} v[N];


struct Line{
	mutable long long k , m , p;
	bool operator<(const Line& o) const{
		return k < o.k;
	}
	bool operator<(long long x) const{
		return p < x;
	}
};


struct LineContainer:multiset<Line,less<>>{
	const long long inf = LLONG_MAX;
	long long div(long long a , long long b){
		return a / b - ((a^b) < 0 && a % b);
	}
	bool isect(iterator x , iterator y){
		if(y == end()){
			x->p = inf;
			return false;
		}
		if(x->k == y->k)
			x->p = x->m > y->m ? inf : -inf;
		else
			x->p = div(y->m - x->m , x->k - y->k);
		return x->p >= y->p;		
	}
	void add(long long k , long long m){
		auto z = insert({k,m,0}) , y = z++ , x = y;
		while(isect(y,z))
			z = erase(z);
		if(x != begin()  && isect(--x,y))
			isect(x , y = erase(y));
		while((y = x) != begin() && (--x)->p >= y->p)
			isect(x,erase(y));
	}
	long long query(long long x){
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};
ll ans[N];
ll s[N];
int n;
LineContainer cht;
int mx[N] , mn[N] , id[N] , valores[N] , cnt[N];
vector<ll> buffer[N];
int32_t main(){
	scanf("%d" , &n);
	for(int i = 1; i <= n; i ++)
		mx[i] = -INT_MAX , mn[i] = INT_MAX;
	for(int i = 1; i <= n; i ++){
		scanf("%d%d" , &v[i].type, &v[i].level);
		mx[v[i].type] = max(mx[v[i].type] , v[i].level);
		mn[v[i].type] = min(mn[v[i].type] , v[i].level);
 		valores[i] = v[i].level;
 		ans[0] += v[i].level;
 		cnt[v[i].type]++;
 	}
	sort(v+1,v+1+n,[&](insect a , insect b){
		return a.level < b.level;
	});
	sort(valores+1,valores+1+n);
	for(int i = 1 ; i<= n; i ++){
		id[v[i].type] = (int)(lower_bound(valores + 1 , valores + 1 + n , mn[v[i].type]) - valores);
		s[i] = s[i-1] + v[i].level;
	}
	multiset<ll> opt;
	for(int i = 1; i <= n; i ++){
		if(cnt[i] > 1){
			buffer[id[i]].push_back(i);
			opt.insert(mx[i]);
		}
	}
	for(int i = n ; i >= 1; i --){
		for(auto w : buffer[i]){
			opt.erase(opt.find(mx[w]));
			cht.add(mx[w] , mx[w] - mn[w]);
		}
		if((cht).size())
			ans[i] = max(ans[i] , -s[i-1] + cht.query(i-1) + ans[0]);
		if(opt.size())
			ans[i] = max(ans[i] , *prev(end(opt))*i - s[i] + ans[0]);
	}
	for(int i = 1; i <= n; i ++){
		ans[i] = max(ans[i] , ans[i-1]);
		printf("%lld\n" , ans[i]);
	}

}	
