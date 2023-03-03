// Acha para cada strings todas as outras que ocorrem como substring
// Depois maximum independent set gerado por isso
// Birthday:
// https://codeforces.com/contest/590/problem/E


const int N = 755;

bitset<N> g[N];
const int MX = 1e7 + 10;
bitset<MX> term;
map<int,set<int> > here;

struct AhoCorasick {
	enum {alpha = 2, first = 'a'};
	struct Node {
		// (nmatches is optional)
		int back, next[alpha];
    Node(int v) { memset(next, v, sizeof(next)); }
	};
	vector<Node> N;
  vector<int> fim;
	void insert(string& s, int j) {
		assert(!s.empty());
		int n = 0;
		trav(c, s) {
			int& m = N[n].next[c - first];
			if (m == -1) { n = m = sz(N); N.emplace_back(-1); }
			else n = m;
		}
    term[n] = 1;
    fim[j] = n;  
  }
	AhoCorasick(vector<string>& pat) {
		N.emplace_back(-1);
    fim.resize(sz(pat));
		rep(i,0,sz(pat)) insert(pat[i], i);
		N[0].back = sz(N);
		N.emplace_back(0);

		queue<int> q;
    vi order;
		for (q.push(0); !q.empty(); q.pop()) {
			int n = q.front(), prev = N[n].back;
			order.pb(n);
      rep(i,0,alpha) {
				int &ed = N[n].next[i], y = N[prev].next[i];
				if (ed == -1) ed = y;
				else {
					N[ed].back = y;
					q.push(ed);
				}
			}
		}
    for(auto n : order){
      if(term[N[n].back]){
        // ok
      }else if(N[n].back){
        N[n].back = N[N[n].back].back;
      }
    }
	}
  void walk(int n,int id){
    if(term[n])
      here[n].insert(id);
    
    n = N[n].back;
    while(n && !here[n].count(id)){
      here[n].insert(id);
      n = N[n].back;
    }
  }
	int find(string word,int id) {
		int n = 0;
		trav(c, word) {
			n = N[n].next[c - first];
      walk(n,id);
		}
    return n;
	}

};

struct Dinic {
	...
};


int n;
int vis[N];
void dfs(int v){//get transitive closure
  if(vis[v])return;
  vis[v]=1;
  rep(i,0,n)if(g[v][i]){
    dfs(i);
    g[v]|=g[i];
  }
}

int in[N],out[N];
int pos[N];

int32_t main(){
  fastio;
  cin >> n;
  vector<string> pat(n);

  rep(i,0,n){
    cin >> pat[i];
  }
  AhoCorasick aho(pat);
  
  rep(i,0,n){
    pos[i] = aho.find(pat[i],i);
  }

  rep(i,0,n)for(auto to : here[pos[i]]){
    if(to!=i){
      g[to][i] = 1;
    }
  }

  int cur=0;
  rep(i,0,n){
    if(!vis[i]){
      dfs(i);
    }
    in[i] = cur++,out[i] = cur++;
  }
  int s = cur++,t=cur++;
  Dinic D(cur+10);
  rep(i,0,n){
    D.addEdge(s,in[i],1);
    rep(j,0,n)if(g[i][j]){
      assert(i!=j);
      D.addEdge(in[i],out[j],1);
    }
    D.addEdge(out[i],t,1);
  }

  cout << n-D.calc(s,t) << endl;
  rep(i,0,n){
    int ok = 0;
    if(D.leftOfMinCut(in[i]) && !D.leftOfMinCut(out[i]))ok=1;
    if(ok)cout<<i+1<<" ";
  }
  cout << endl;
}
