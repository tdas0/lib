#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
	int n;
	cin >> n;
	ll res=0;
	for(int i=0;i<n;i++){
		ll r;
		cin >> r;
		res+=r*r;
	}
	if(res%2==0){
		cout << (res/2)<<endl;
	}else{
		cout<<(res/2)<<".5"<<endl;
	}
}
