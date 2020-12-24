#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
typedef long long ll;
typedef pair<int,int> pii;
typedef vector<pii> vpi;
vpi ans;
map<pii, int> rf;
int ask(int x ,int y){
	if(rf.count({x,y})) return rf[{x,y}];
	cout <<"? " << x <<" " << y << endl;
	cout.flush();
	cin >> rf[{x,y}];
	return rf[{x,y}];
}

int menor(int x , int y){
	int cnt = 0 ;
	for(int i = 0 ; i < ans.size() ; i ++){
		if(ans[i].first <= x && ans[i].second <= y) cnt ++ ;
	}
	return cnt;
}


void solve(int x){
	int atual = 0 ;
	int last = ask(x, (int) 1e7) - menor(x-1 , (int) 1e7);
	while(atual != last){
		int l = -(int) 1e6, r = (int) 1e6;
		int ansj = -1;
		while(l<=r){
			int mid = l +(r-l)/2;
			int k = ask(x,mid) - menor(x-1,mid);
			if(atual < k){
				ansj = mid;
				r = mid - 1;
			}
			else l = mid + 1;
		}
		ans.push_back({x,ansj});
		atual = ask(x,ansj) - menor(x-1 , ansj);
	}
}

int32_t main(){
	int n;
	cin >> n;
	int sj = 0;
	set<int> x;
	for(int i = 1 ; i <= n; i ++){
		int l = - (int) 1e6 , r = (int) 1e6;
		int ansj = -1;
		while(l<=r){
			int mid = l + (r-l)/2;
			int k = ask(mid, (int) 1e7);
			if(k >= i){
				ansj = mid;
				r = mid - 1;
			}	
			else l = mid + 1; 
		}
		x.insert(ansj);
	}
	for(set<int>::iterator it = x.begin() ; it != x.end() ; it ++ ){
		solve(*it);
	}
	cout <<"! " ; 
	for(int i = 0 ; i < ans.size() ; i ++){
		cout << ans[i].first <<" " << ans[i].second ;
		if((i+1) != ans.size()) cout <<" ";
	}
	cout.flush();
	cout << endl;
}