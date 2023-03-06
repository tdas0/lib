/* Finds for every interval on the suffix array [lSA,rSA]
 * The maximum sizes before this merges with another interval
 * This can be though as the reverse of a DFS on suffix tree
 * All leafs from [lSA,rSA] are equal from size [tamL,tamR]. For <tamL or >tamr
 * There will be more leafs added
 * Source: NaimSS
 * Status: tested on https://codeforces.com/contest/1780/problem/G
 */

struct suffixInter{
    int lSA,rSA,tamL,tamR;
    // both inclusive
};
struct dsu{
    vi p,ps,L,R;
    vi lastSz;
    vector<suffixInter> vec;
    dsu(vi sa){
        p = ps = L = R = lastSz = vi(sz(sa));
        rep(i,0,sz(sa)){
            p[i] = L[i] = R[i] = i;
            ps[i]=1;
            lastSz[i] = sz(sa)-1 - sa[i];
            // -1 por causa do # no final
        }
    }
    int f(int x){return p[x]=(p[x]==x?x:f(p[x]));}
    bool join(int a,int b,int LCP){
        a=f(a),b=f(b);
        if(a==b)return 0;
        
        pushVec(a,LCP);
        pushVec(b,LCP);

        if(ps[a] > ps[b])swap(a,b);
        ps[b]+=ps[a];
        p[a]=b;
        L[b] = min(L[b],L[a]);
        R[b] = max(R[b],R[a]);
        lastSz[b] = LCP;
        return 1;
    }
    void pushVec(int p,int LCP){
        if(LCP!=lastSz[p])
            vec.pb({L[p],R[p],LCP+1,lastSz[p]});
    }
};


vector<suffixInter> dsuOnLCP(string &s){
    SuffixArray sa(s);
    vector<pii> segs;
    for(int i=0;i<sz(sa.lcp);i++){
        segs.pb(pii(sa.lcp[i],i));
    }
    sort(all(segs),greater<pii>());
    dsu d(sa.sa);
    for(auto [lcp,pos] : segs){
        if(pos)d.join(pos-1,pos,lcp);
    }
    return d.vec;
}


// for problem on codeforces:
  auto vec = dsuOnLCP(s);

  for(auto [lsa,rsa,taml,tamr] : vec){
    int occ = rsa-lsa+1;
    if(occ < taml)continue;
    qry[taml-1].pb(pii(occ,-1));
    qry[tamr].pb(pii(occ,+1));
  }
  ll res=0;
  for(int t=1;t<=n;t++){
    for(int occ = t;occ <= n;occ += t){
        numDiv[occ] ++;
    }
    for(auto [occ,sinal] : qry[t]){
        res += 1ll * occ * sinal * numDiv[occ];
    }
  }
  cout << res << endl;
