#include <bits/stdc++.h>
#pragma comment(linker, "/STACK: 2000000")
using namespace std;
typedef vector<int> vi;
int x[101010] , y[101010];
int cnt = 0;
int n ;
map<pair<int,int> , string> ans;

string ask(int x , int y){
	if(ans.count({x,y})) return ans[{x,y}];
	cnt ++ ;
	assert(1 <= x && x <= n/2);
	assert(1 <= y && y <= (n+1)/2);
	cout << "? " << x <<" " << y << endl;
	string s;
	cin >> s;
	return ans[{x,y}] = s;
}

void print(){
	cout <<"! " ;
	for(int i = 1 ;i <= n/2 ; i++) cout << 2*x[i] << " ";
	for(int i = 1 ;i <= (n+1)/2 ; i ++) cout << y[i] <<" ";
	exit(0);
}

vector< vi> o;

int32_t main(){
	srand(0x600DCAFE);
	vi e;
	cin >> n;
	if(n == 1){
		y[1] = 1;
		print();
	}
	for(int i = 1 ; i <= n/2 ; i++) e.push_back(i);
	o.push_back(vector<int>());
	for(int i = 1; i <=(n+1)/2 ; i ++) o[0].push_back(i); 
	for(int i = 0 ; i < e.size() ; i ++){
		int l = 0 , r = ((int)o.size()) - 1;
		int ans = ((int)o.size()) - 1;
		while(l<=r){
			int mid = (l+r)/2;
			if(ask(e[i] , o[mid][0]) == "<"){
				ans = mid;
				r = mid - 1;
			}
			else l = mid + 1;
		}
		vi a , b , c , d;
		if(ans){
			for(int j = 0 ; j < o[ans-1].size() ; j ++){
				if(ask(e[i] , o[ans-1][j]) == ">"){
					a.push_back(o[ans-1][j]);
				}
				else b.push_back(o[ans-1][j]);
			}
		}
		for(int j = 0 ; j < o[ans].size() ; j ++){
			if(ask(e[i] , o[ans][j]) == ">"){
				c.push_back(o[ans][j]);
			}
			else d.push_back(o[ans][j]);
		}		
		vector<vi> p;
		for(int j = 0 ; j < ans - 1; j ++ ){
			p.push_back(o[j]);
			x[e[i]] += o[j].size();
		}
		x[e[i]] += a.size() + c.size();
		if(a.size()) p.push_back(a);
		if(c.size()) p.push_back(c);
		if(b.size()) p.push_back(b);
		if(d.size()) p.push_back(d);
		for(int j = ans +1 ; j < o.size(); j ++){
			p.push_back(o[j]);
		}
		swap(p,o);
	}
	for(int i = 0 ; i <o.size() ; i ++){
		y[o[i][0]] = 2*i + 1;
	}
	print();
}