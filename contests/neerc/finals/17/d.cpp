#include <bits/stdc++.h>
#define endl '\n'
#define pb push_back
#define MAXN 100100
#define ff first
#define ss second
#define int long long
#define fastio ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
int n,m,k;

struct coisa{
 int x,y,z;
 coisa(){}
 coisa(int a,int b,int c){
 	x = a;
 	y = b;
 	z = c;
 }
};

int32_t main(){
	fastio;
	int a,b,c;
	cin>>a>>b>>c;
	vector<coisa> v;
	if(a >= max(b,c)){
		// solve(x,y);
		if(a>b*c){
			cout<<-1<<endl;
			return 0;
		}
		if(a>=b+c-1){
			int aa = a;
			v.pb(coisa(0,0,0));
			aa--;
			for(int i=1;i<b;i++){
				v.pb(coisa(i,0,0));
				aa--;
			}
			for(int i=1;i<c;i++){
				v.pb(coisa(0,i,0));
				aa--;
			}
			for(int i=1;i<b;i++){
				for(int j=1;j<c;j++){
					if(aa==0)break;
					aa--;
					v.pb(coisa(i,j,0));
				}
			}

		}else{

			if(b < c){
				int aa = a;
				for(int i=0;i<b;i++){
					v.pb(coisa(i,i,0));
					aa--;
				}
				int cc = c-b;
				int f=b-1;
				for(int i=b;;i++){
					if(cc==0)break;
					cc--;
					aa--;
					f = i;
					v.pb(coisa(b-1,i,0));
				}
				for(int i=0;i<b;i++){
					for(int j=1;j<=f;j++){
						if(aa==0)break;
						aa--;
						v.pb(coisa(i,j,0));
					}
				}
			}else{
				int aa = a;
				for(int i=0;i<c;i++){
					v.pb(coisa(i,i,0));
					aa--;
				}
				int bb = b-c;
				int f=c-1;
				for(int i=c;;i++){
					if(bb==0)break;
					bb--;
					aa--;
					f = i;
					v.pb(coisa(i,c-1,0));
				}

				for(int i=0;i<c;i++){
					for(int j=1;j<=f;j++){
						if(aa==0)break;
						aa--;
						v.pb(coisa(j,i,0));
					}
				}

			}

		}

	}else if(b>=max(a,c)){

		if(b>a*c){
			cout<<-1<<endl;
			return 0;
		}
		if(b>=a+c-1){
			int bb = b;
			v.pb(coisa(0,0,0));
			bb--;
			for(int i=1;i<a;i++){
				v.pb(coisa(i,0,0));
				bb--;
			}
			for(int i=1;i<c;i++){
				v.pb(coisa(0,0,i));
				bb--;
			}
			for(int i=1;i<a;i++){
				for(int j=1;j<c;j++){
					if(bb==0)break;
					bb--;
					v.pb(coisa(i,0,j));
				}
			}

		}else{

			if(a < c){
				int bb = b;
				for(int i=0;i<a;i++){
					v.pb(coisa(i,0,i));
					bb--;
				}
				int cc = c-a;
				int f=a-1;
				for(int i=a;;i++){
					if(cc==0)break;
					cc--;
					bb--;
					f = i;
					v.pb(coisa(a-1,0,i));
				}
				for(int i=0;i<a;i++){
					for(int j=1;j<=f;j++){
						if(bb==0)break;
						bb--;
						v.pb(coisa(i,0,j));
					}
				}
			}else{
				int bb = b;
				for(int i=0;i<c;i++){
					v.pb(coisa(i,0,i));
					bb--;
				}
				int aa = a-c;
				int f=c-1;
				for(int i=c;;i++){
					if(aa==0)break;
					aa--;
					bb--;
					f = i;
					v.pb(coisa(i,0,c-1));
				}

				for(int i=0;i<c;i++){
					for(int j=1;j<=f;j++){
						if(bb==0)break;
						bb--;
						v.pb(coisa(j,0,i));
					}
				}

			}

		}


	}else{


		if(c>a*b){
			cout<<-1<<endl;
			return 0;
		}
		if(c>=a+b-1){
			int cc = c;
			v.pb(coisa(0,0,0));
			cc--;
			for(int i=1;i<a;i++){
				v.pb(coisa(0,i,0));
				cc--;
			}
			for(int i=1;i<b;i++){
				v.pb(coisa(0,0,i));
				cc--;
			}
			for(int i=1;i<a;i++){
				for(int j=1;j<b;j++){
					if(cc==0)break;
					cc--;
					v.pb(coisa(0,i,j));
				}
			}

		}else{

			if(a < b){
				int cc = c;
				for(int i=0;i<a;i++){
					v.pb(coisa(0,i,i));
					cc--;
				}
				int bb = b-a;
				int f=a-1;
				for(int i=a;;i++){
					if(bb==0)break;
					bb--;
					cc--;
					f = i;
					v.pb(coisa(0,a-1,i));
				}
				for(int i=0;i<a;i++){
					for(int j=1;j<=f;j++){
						if(cc==0)break;
						cc--;
						v.pb(coisa(0,i,j));
					}
				}
			}else{
				int cc = c;
				for(int i=0;i<b;i++){
					v.pb(coisa(0,i,i));
					cc--;
				}
				int aa = a-b;
				int f=b-1;
				for(int i=b;;i++){
					if(aa==0)break;
					aa--;
					cc--;
					f = i;
					v.pb(coisa(0,i,b-1));
				}

				for(int i=0;i<b;i++){
					for(int j=1;j<=f;j++){
						if(cc==0)break;
						cc--;
						v.pb(coisa(0,j,i));
					}
				}

			}

		}



	}








	cout<<v.size()<<endl;
	for(coisa x : v){
		cout<<x.x<<" "<<x.y<<" "<<x.z<<endl;
	}
	return 0;



}	