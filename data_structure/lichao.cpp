/**
 * Author: tdas
 * Date: ??? 2019
 * License: CC0
 * Source: folklore
 * Description: L***
 * Time: $O(nlogn)$
 */
// https://codeforces.com/contest/319/submission/46887901
#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
#define ll long long
ll dp[N] , A[N] , B[N] , n;
struct line{
    ll x , y;
    ll eval(ll k){
    	return k*x+y;
    }
};

struct node{
	ll l , r;
	line best;
	node * left ,* right;
};

node * lichao;


void update(line curr, node *& tree){
	ll l = tree->l , r = tree->r;
	ll mid = (l+r)/2;
	bool lf = curr.eval(l) < tree->best.eval(l);
	bool mf = curr.eval(mid) < tree->best.eval(mid);
	if(mf){
		swap(tree->best, curr);
	}
	if(l >= r) return ;
	if(mf != lf){
		if(!tree->left){
			tree->left = new node();
			tree->left->l = l , tree->left->r = mid , tree->left->best = curr;
		}
		else update(curr, tree->left);
	}	
	else{
		if(!tree->right){
			tree->right = new node();
			tree->right->l = mid + 1 , tree->right->r = r , tree->right->best = curr;
		}
		else update(curr, tree->right);
	}
}

ll query(ll x , node* tree){	
	ll l = tree->l , r = tree->r;
	ll mid = (l+r)/2;
	if(l == r && l == x){
		return tree->best.eval(x);
	}
	if(x <= mid){
		if(tree->left) return min(tree->best.eval(x) , query(x , tree->left));
	}
	if(x > mid) if(tree->right) return min(tree->best.eval(x) , query(x,tree->right));
	return tree->best.eval(x);
}



int32_t main(){
	scanf("%lld" , &n);
	for(int i = 1 ; i <= n ; i ++) scanf("%lld" , &A[i]);
	for(int i = 1 ; i <= n ; i ++) scanf("%lld" , &B[i]) , dp[i] = (ll) 1e18;
	lichao = new node();
	dp[1] = B[1];
	lichao->l = 0 , lichao->r = (ll) 1e9;
	lichao->best = {B[1] , 0};
	for(int i = 2  ;i <= n; i ++){
		dp[i] = query(A[i], lichao);
        update({B[i] , dp[i]}, lichao);
	}
	printf("%lld\n" , dp[n]);
}
