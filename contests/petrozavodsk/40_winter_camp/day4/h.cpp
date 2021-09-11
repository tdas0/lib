#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<b;i++)
#define pb push_back
#define ff first
#define ss second
#define all(x) x.begin(),x.end()
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl;
using namespace std;
typedef pair<int,int> pii;
#define endl '\n'
typedef long long ll;
typedef vector<int> vi;

const int N = 1000010;
int ans[N];

int sz[N];
int val[N],mx[N];
int L[N],R[N];
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)




int n,m;
int st[N];
int pai[N];


void dfs(int i){
		int A = L[i],B = R[i];
		if(A)dfs(A);
		if(B)dfs(B);
		mx[i] = val[i];
		sz[i] = 1;
		ans[i] = (val[i] > 1 ? 1 : 0);
		//db3(i,A,B);
		
		if(ans[A] > ans[i])ans[i] = ans[A];
		if(ans[B] > ans[i])ans[i] = ans[B];

		if(mx[B] + val[i] > sz[B] + 1)
			ans[i] = max(ans[i],sz[B] + 1 + min(sz[A],(mx[B] + val[i] - 1 - (sz[B] + 1))));
		
		
		if(mx[A] + val[i] > sz[A] + 1)
			ans[i] = max(ans[i],sz[A] + 1 + min(sz[B],(mx[A] + val[i] - 1 - (sz[A] + 1))));

		if(mx[A] > mx[i])mx[i] = mx[A];
		if(mx[B] > mx[i])mx[i] = mx[B];
		sz[i] = 1 + sz[A] + sz[B];
}

int solve(){
	sz[0] = 0,mx[0] = -1e9;
	rep(i,0,n+1){
		L[i] = R[i] = 0;
		pai[i] = 0;
	}
	int ptr=0;
	st[0] = 0;
	int root = 0;
	for(int i=1;i<=n;i++){
		int ant = i-1;
		while(ant!=0 and val[ant] > val[i]){
			ant = pai[ant];
		}
		if(ant){
			L[i] = R[ant];
			pai[i] = ant;
			R[ant] = i;
		}else{
			L[i] = root;
			pai[i] = 0;
			root = i;
		}
	}
	

	dfs(root);

	return ans[root];
}


int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&val[i]);
	}

	printf("%d\n",solve());
	while(m--){
		int k;
		
		scanf("%d",&k);
		
		while(k--){
			int a,b;
			scanf("%d%d",&a,&b);
			swap(val[a],val[b]);
		}

		printf("%d\n",solve());
	}
}
