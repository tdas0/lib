#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int a[N] , b[N] , cur[N];


int32_t main(){
	int n , m;
	scanf("%d%d" , &n , &m);
	for(int i =1 ; i <= n; i ++)
		scanf("%d" , &a[i]);
	for(int i = 1 ;i <= m; i ++)
		scanf("%d" , &b[i]);
	int ans = 0;
	int l = 0 , r = n + m;
	while(l<=r){
		int mid = l + (r-l)/2;
		for(int i = 1; i <= n; i ++){
			cur[i] = a[i];
		}
		for(int i = 1 ; i <= min(i , mid) ; i ++){
			cur[b[i]] ^= 1;
		}
		int cnt = 0;
		for(int i = 1; i <= n; i ++){
			cnt += cur[i];
		}
		if(cnt <= mid){
			ans = mid;
			r = mid - 1;
		}
		else
			l = mid + 1;
	}
	cout << ans << endl;
}
