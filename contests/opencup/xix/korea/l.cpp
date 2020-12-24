#include <bits/stdc++.h>

using namespace std;

const int N = 100005;

int n , q;
int C[320] , D[320];
int a[N];
int leq[N] , ge[N];
int32_t main(){
	scanf("%d" , &n);
	for(int i = 1; i <=n ; i ++) scanf("%d" , &a[i]);
	for(int x = 2; x < 320 ; x ++){
		int j = 1 ;
		while(j <= n){
			bool t = false;
			int bad = 0;
			C[x] ++ ;
			if(j == n){
				break ;
			}
			if(a[j] <= a[j+1]){
				t = true;
			}
			if(t){
				int cz = 1;
				while(j < n && a[j+1] >= a[j]){
					j ++ ; 
					cz ++ ;
				}
				while(j < n && cz < x){
					j ++ ;
					cz ++ ;
					bad ++ ;
				}
			}
			else{
				int cz = 1;
				while(j < n && a[j+1] < a[j]){
					j ++;
					cz ++;
				}
				while(j < n && cz < x){
					j ++ ;
					cz ++ ;
					bad ++ ;
				}
			}
			D[x] += bad;
			j++;
		}			
	}
	ge[n] = n, leq[n] = n;
	for(int i = n - 1 ; i >= 1; i --){
		if(a[i] <= a[i+1]){
			ge[i] = i , leq[i] = leq[i+1];
		}
		else{
			ge[i] = ge[i+1] , leq[i] = i;
		}
	}
	scanf("%d" , &q);
	while(q--){
		int x;
		scanf("%d" , &x);
		if(x >= sqrt(N)){ // do it
			int j = 1;
			int c = 0 , d = 0;
			while(j <= n){
				c++;
				int ptr = max(ge[j] , leq[j]);
				int r = ptr - j + 1 ;
				int left = n - (j + r - 1);
				int bad = max(min(left, x - r),0);
				d += bad;
				j += max(r , x); 
			}
			printf("%d %d\n" , c, d);
		}
		else{
			printf("%d %d\n" , C[x] , D[x]);
		}
	}
}