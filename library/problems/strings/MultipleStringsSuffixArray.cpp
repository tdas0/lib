// Sample example of a problem with an array A of strings
// as input. Output is for each i the number of substrings Ai[L...R]
// That appear in at least K strings including i.
// Little Elephant and strings:
// https://codeforces.com/problemset/problem/204/E

struct SuffixArray {
	vi sa, lcp;
	SuffixArray(string& s, int lim=256) { // or basic_string<int>
		int n = sz(s) + 1, k = 0, a, b;
		vi x(all(s)+1), y(n), ws(max(n, lim)), rank(n);
		sa = lcp = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(all(y), n - j);
			rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			rep(i,0,n) ws[x[i]]++;
			rep(i,1,lim) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		rep(i,1,n) rank[sa[i]] = i;
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for (k && k--, j = sa[rank[i] - 1];
					s[i + k] == s[j + k]; k++);
	}
};


const int N = 200100; //
string s[N];
int ini[N];
int onde[N];
ll resp[N];

int pai[N];
set<int> ids[N];
vector<int> suffix[N];

int find(int x){
    return pai[x] = (pai[x]==x?x:find(pai[x]));
}

void join(int a,int b){
    a=find(a),b=find(b);
    if(a==b)return;
    if(sz(ids[a]) > sz(ids[b]))swap(a,b);
    pai[a]=b;
    for(auto it : ids[a])ids[b].insert(it);
    for(auto it : suffix[a])suffix[b].pb(it);
}

int32_t main(){
    fastio;
    int n,k;
    cin >> n >> k;
    string t="";
    rep(i,0,n){
        cin >> s[i];
        ini[i] = sz(t);
        t+=s[i];
        t+='#';
        if(k == 1)cout << 1ll * sz(s[i])*(sz(s[i])+1)/2 <<  " ";
        for(int j=ini[i];j<sz(t);j++)onde[j]=i;
    }
    if(k==1){
        cout<<"\n";
        return 0;
    }
    SuffixArray sa(t);
    rep(i,1,sz(t)+1){
        pai[i]=i;
        if(t[sa.sa[i]]!='#'){
            ids[i].insert(onde[sa.sa[i]]);
            suffix[i].pb(sa.sa[i]);
        }
    }
    for(int i=1;i<=sz(t);i++){
        int pos = sa.sa[i];
        if(t[pos] == '#'){
            sa.lcp[i] = 0;
            continue;
        }
        int mx = sz(s[onde[pos]]) - (pos-ini[onde[pos]]);
        sa.lcp[i] = min(sa.lcp[i],mx);
    }

    vector<pii> ev;
    for(int i=1;i<=sz(t);i++){
        ev.pb(pii(sa.lcp[i],i));
    }
    sort(all(ev),greater<pii>());

    for(auto it : ev){
        int pos = it.ss;
        int lcp = it.ff;
        if(lcp==0)break;
        // juntar pos com pos-1
        if(pos==0)continue;
        join(pos-1,pos);
        int rep = find(pos);
        if(sz(ids[rep])>=k){
            for(auto it : suffix[rep]){
                resp[onde[it]]+=lcp;
            }
            suffix[rep].clear();
        }
    }

    rep(i,0,n){
        cout << resp[i]<<" \n"[i==n-1];
    }
    

    // math -> gcd it all
    // Did u check N=1? Did you switch N,M?
}
