#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define int long long
#define double long double
using namespace std;


int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);
    int test;
    cin>>test;
    while(test--){
        int q , g;
        cin>>q>>g;
        vector<int> w(q);
        int soma =0, sum2=0;
        for(int i = 0; i < q; i++){
            cin>>w[i];
            w[i] = abs(w[i]);
            soma += w[i];
            sum2 += w[i]*w[i];
        }
        int F=0, C=0;
        for(int i=0;i<q;i++){
            int fi,ci;
            cin>>fi>>ci;
            F += fi;
            C+=ci;
        }
        if(C<=0){
        	cout << 0 << endl;
        	continue;
        }

        double alpha= g*sqrt(sum2);

        assert(alpha-F>0.0);

        cout<<setprecision(20)<<fixed;
        cout<<max((double)0.0, (1.0*C/(alpha-F)))<<"\n";
    }
}