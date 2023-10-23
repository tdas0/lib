#include <bits/stdc++.h>
#define pb push_back
#define sz(v) ((int)v.size())
using namespace std;
#define rep(i,a,b) for (int i = (a); i < (b); i++)
#define all(X) begin(X), end(X)
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int is_ok(string& s,string &t,string &goal,set<char>& letras){

    rep(i,0,sz(s)){
        if(t[i] == 'X'){
            if(letras.count(s[i]))return 0;
        }else if(t[i] == '!'){
            if(!letras.count(s[i]))return 0;
            if(s[i] == goal[i])return 0;
        }else{
            // *
            if(s[i] != goal[i])return 0;
        }
    }
    return 1;
}


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    vector<string> s(n);
    rep(i,0,n){
        cin >> s[i];
    }
    int q;
    cin >> q;
    set<char> letras;
    for(auto &c : s[0])letras.insert(c);
    while(q--){
        string t;
        cin >> t;
        int res=0;
        for(int i=0;i<n;i++){
            if(is_ok(s[i],t,s[0],letras))res++;
        }
        cout << res << endl;
    }
}
