#include <bits/stdc++.h>
using namespace std;
#define sz(x) (x).size()


int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	while(t--){
		int n ; char k;
		string s , t;
		cin >> n >> k >> s >> t;
		bool has = false;
		string ans;
		for(int i = 0 ; i < n; i ++){
			if(s[i] == t[i]){
				if(s[i] == k){
					has = true;
				}
				ans.push_back(s[i]);
			}
			else if(!has){
				string rollback = ans;
				if(s[i] < k && k < t[i]){
					ans.push_back(k) , has = true;
					for(int j = i + 1; j < n; j ++)
						ans.push_back('a');
				}
				if(s < ans && ans < t && sz(ans) == sz(s) && has){
					break;
				}
				if(t[i] - s[i] > 1){
					ans.push_back((char)(s[i] + 1));
					for(int j = i + 1; j < n; j ++)
						ans.push_back(k) , has = true;
				}
				if(s < ans && ans < t && sz(ans) == sz(s) && has){
					break;
				}
				// escolhe s[i]
				ans.push_back(s[i]);
				bool any = false;
				for(int j = i + 1; j < n; j ++){
					if(any){
						ans.push_back(k);
						has = true;
					}
					else{
						if(s[j] < k){
							ans.push_back(k);
							has = true;
							any = true;
						}
						else if(s[j] != 'z'){
							if(k == 'z')
								has = true;
							ans.push_back('z');
							any = true;
						}
						else{
							ans.push_back(s[j]);
							if(s[j] == k)
								has = true;
						}
					}
				}
				if(s < ans && ans < t && sz(ans) == sz(s) && has){
					break;
				}
				// escolhe t[i]
				ans = rollback;
				ans.push_back(t[i]);
				for(int j = i + 1; j < n; j ++){
					if(any){
						ans.push_back(k);
						has = true;
					}
					else{
						if(t[j] > k){
							ans.push_back(k);
							has = true;
							any = true;
						}
						else if(t[j] != 'a'){
							ans.push_back('a');
							if(t[j] == 'a')
								has = true;
							any = true;
						}
						else{
							ans.push_back(t[j]);
							if(t[j] == k)
								has = true;
						}
					}
				}
				break;
			}
			else{
				if(t[i] - s[i] > 1){
					ans.push_back((char) (s[i] + 1));
					for(int j = i + 1; j < n; j ++)
						ans.push_back(k);
					has = true;
					break;
				}
				else{
					string rollback = ans;
					// tenta s[i]
					ans.push_back(s[i]);
					bool any = false;
					for(int j = i + 1; j < n; j ++){
						if(any){
							ans.push_back(k);
						}
						else{
						 	if(s[j] != 'z'){
								ans.push_back('z');
								any = true;
							}
							else
								ans.push_back(s[j]);
						}
					}
					if(s < ans && ans < t && sz(ans) == sz(s) && has){
						break;
					}
					ans = rollback;
					ans.push_back(t[i]);
					for(int j = i + 1; j < n; j ++){
						if(any){
							ans.push_back(k);
							has = true;
						}
						else{
							if(t[j] != 'a'){
								ans.push_back('a');
								any = true;
							}
							else
								ans.push_back(t[j]);
						}
					}
					break;									
				}
				break;
			}
		}
		if(!has || !(s < ans && ans < t) || (sz(ans) != sz(s)))
			cout <<"NO" << endl;
		else
			cout << ans << endl; 
	}	
}
