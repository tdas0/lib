#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 300005;
ll cost[N][5] , ans[6];
map<pair<int,int>,int> cnt[6];
pair<int,int> pos[N];
ll resp[N];
// U , R , D , L
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

ll f(int x , int y , int k){
	ll i = k;
	ll ha = (abs(x)+1) ^ (abs(y)+1);
	ll he = i * (i+1) / 2ll;
	return he*(ha+1ll);
}


int32_t main(){
	int n;
	cin >> n;
	string s;
	cin >> s;
	pair<int,int> u = {0,0};
	cnt[0][u]++;
	ans[0] = 1;
	for(int i = 1; i <= (int) s.size() ; i ++){
		auto w = s[i-1];
		if(w == 'U'){
			u.first += dx[0] , u.second += dy[0];
		}
		if(w == 'R'){
			u.first += dx[1] , u.second += dy[1];
		}
		if(w == 'D'){
			u.first += dx[2] , u.second += dy[2];
		}
		if(w == 'L'){
			u.first += dx[3] , u.second += dy[3];
		}
		cnt[0][u]++;
		ans[0] += f(u.first,u.second,cnt[0][u]) - f(u.first,u.second,cnt[0][u]-1);
		cost[i][0] = ans[0];
		pos[i] = u;
		if(i + 1 == (int) s.size()){
			resp[i+1] = ans[0];
		}
	}
	map<pair<int,int> ,int> cnt2 = cnt[0];
	for(int j = 1; j < 5; j ++)
		ans[j] = ans[0];
	for(int i = (int) s.size() ; i >= 1; i --){
		for(int j = 1; j <5; j ++)
			ans[j] += f(pos[i].first,pos[i].second,cnt2[pos[i]]+cnt[j][pos[i]] -1) - f(pos[i].first,pos[i].second,cnt2[pos[i]]+cnt[j][pos[i]]);
		cnt2[pos[i]]--;
		for(int j = 0 ; j < 4; j ++){
			pair<int,int> v = {pos[i].first + dx[j] , pos[i].second + dy[j]};
			ans[j+1] += f(v.first,v.second,cnt2[v] + cnt[j+1][v]+1) - f(v.first,v.second,cnt2[v] + cnt[j+1][v]); 
			cnt[j+1][v]++;
		}	
		if(i > 1){
			auto w = s[i-2];
			if(w == 'D'){
				ll ha = f(pos[i-1].first,pos[i-1].second,cnt2[pos[i-1]] + cnt[1][pos[i-1]] - 1) - f(pos[i-1].first,pos[i-1].second,cnt2[pos[i-1]] + cnt[1][pos[i-1]]);
				resp[i-1] = ans[1] + ha;
			}
			if(w == 'L'){
				ll ha = f(pos[i-1].first,pos[i-1].second,cnt2[pos[i-1]] + cnt[2][pos[i-1]] - 1) - f(pos[i-1].first,pos[i-1].second,cnt2[pos[i-1]] + cnt[2][pos[i-1]]);	
				resp[i-1] = ans[2] + ha;
			}
			if(w == 'U'){
				ll ha = f(pos[i-1].first,pos[i-1].second,cnt2[pos[i-1]] + cnt[3][pos[i-1]] - 1) - f(pos[i-1].first,pos[i-1].second,cnt2[pos[i-1]] + cnt[3][pos[i-1]]);			
			    resp[i-1] = ans[3] + ha;
			}
			if(w == 'R'){
				ll ha = f(pos[i-1].first,pos[i-1].second,cnt2[pos[i-1]] + cnt[4][pos[i-1]] - 1) - f(pos[i-1].first,pos[i-1].second,cnt2[pos[i-1]] + cnt[4][pos[i-1]]);			
				resp[i-1] = ans[4] + ha;
			}	
		}
	}
	for(int i = 1; i <= n; i ++)
		printf("%lld\n" , resp[i]);
}
