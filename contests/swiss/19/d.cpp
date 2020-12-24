#include <bits/stdc++.h>
#define pb push_back
#define endl '\n'
using namespace std;

const int N = 2020;
int a[N];

int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i+n] = a[i];
	}

	for(int j=1;j<=n;j++){
		vector<int> v,v2;
		for(int it=j;it<j+n;it++){
			v.pb(a[it]);
			v2.pb(a[it]);
		}
		//for(int x : v)cout<<x<<" ";
//cout<<endl;
	//	for(int x : v2)cout<<x<<" ";
		//	cout<<endl;
		sort(v2.begin(),v2.end());
		if(v2==v){
			cout<<"Phew"<<endl;
			return 0;
		}

	}
	cout<<"Lie"<<endl;
	return 0;

}