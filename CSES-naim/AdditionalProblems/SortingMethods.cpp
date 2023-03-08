/*
1-At each step, choose two adjacent elements and swap them.
2-At each step, choose any two elements and swap them.
3-At each step, choose any element and move it to another position.
4-At each step, choose any element and move it to the front of the array.
*/

#include <bits/stdc++.h>
#define int long long
#define MAXN 200100
#define pb push_back
#define ff first
#define ss second
#define fastio ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef pair<int,int> pii;
 
 
int A[MAXN];
 
int bit[MAXN];
 
void update(int x,int val){
	while(x<MAXN){
		bit[x]+=val;
		x+=(x&-x);
	}
}
 
int sum(int x){
	int r=0;
	while(x>0){
		r+=bit[x];
		x-=(x&-x);
	}
	return r;
}
int n;
int res[10];
int LIS(){
	vector<int> pilha;
	for(int i=1;i<=n;i++){
		vector<int>::iterator it = lower_bound(pilha.begin(),pilha.end(),A[i]);
		if(it==pilha.end())pilha.pb(A[i]);
		else *it = A[i];
	}
	return pilha.size();
	
}
 
int pos[MAXN];
int rev[MAXN];
int32_t main(){
	fastio;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>A[i];
		pos[A[i]] = i;
		rev[i] = A[i];
	}
 
	for(int i=1;i<=n;i++){
		if(rev[i]!=i){
			int p = rev[i];
			pos[p] = pos[i];
			rev[pos[p]] = p;
			// ***** //
			rev[i] = i;
			pos[i] = i;
			res[2]++;
		}
	}
	res[3] = n - LIS();
	res[4]=n;
	int mx = n;
	for(int i=n;i>=1;i--){
		if(A[i]==mx){
			res[4]--;
			mx--;
		}
	}
	for(int i=1;i<=n;i++){
		
		if(sum(MAXN-1)-sum(A[i])>0){
			res[1]+=sum(MAXN-1)- sum(A[i]);
		}
		update(A[i],1);
	}
	
	for(int i=1;i<=4;i++)cout<<res[i]<<" ";
	cout<<endl;
}