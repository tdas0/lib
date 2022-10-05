// Source: Tdas + Naimss
// com a sol de alguns problemas do CSES
// 
struct suffix_automaton{
  enum{alpha  = 26 , first = 'a'};
  struct node{
    int len, link;
    vi next;
    int firstpos;
    int cnt;
    node(int x , int y , int v){
      cnt=0;
      len = x , link = y;
      next = vi(alpha);
      rep(i,0,alpha) next[i] = v;
    }

  };
  int last = 0 ;
  vector<node> st; 
  suffix_automaton(int v = 0){st.push_back(node(0,-1,0));}
  void extend(char c){
    c -= first;
    int cur = sz(st) , p,q;
    st.push_back(node(st[last].len + 1,-1,0));
    st[cur].firstpos = st[cur].len -1;
    st[cur].cnt = 1;
      for (p=last; p!=-1 && !st[p].next[c]; p=st[p].link) st[p].next[c] = cur;        
    if(p == -1) st[cur].link = 0 ;
    else{
      q = st[p].next[c];
      if(st[p].len + 1 == st[q].len){
        st[cur].link = q;
      }
      else{
        int clone = sz(st);
        st.push_back(node(st[p].len+1,st[q].link,0));
        st.back().next = st[q].next;
        st[clone].firstpos = st[q].firstpos;
              for (; p!=-1 && st[p].next[c]==q; p=st[p].link)
                  st[p].next[c] = clone;
             
              st[q].link = st[cur].link = clone;

      }
    } 
    last = cur;
  }
  vi terminal(){
    int p = last; vi t;
    while(p >= 0){
      t.push_back(p), p = st[p].link;
    }
    return t;
  }
  // Daqui pra baixo é para problemas especificos, pode tirar!
  int PRECALC=0;
  int Cnt(const string &s){
    calc_cnt();
    int p = 0;
    rep(j,0,sz(s)){
      if(!st[p].next[s[j]-first]) return 0;
      p = st[p].next[s[j]-first];
    }
    return st[p].cnt;
  }
  int First(const string& s){
    int p=0;
    rep(j,0,sz(s)){
      if(!st[p].next[s[j]-first])return -1;
      p = st[p].next[s[j]-first];
    }
    return st[p].firstpos - sz(s) + 2;
  }
  void calc_cnt(){
    if(PRECALC)return;
    vi v;
    PRECALC=1;
    rep(i,0,sz(st))v.pb(i);
    sort(all(v),[&](int a,int b){
      return st[a].len > st[b].len;
    });
    for(int i : v)if(st[i].link>=0)st[st[i].link].cnt+=st[i].cnt;
  }
  pii repeating(int k){ // string q repete K vezes ou -1 se n tem
    calc_cnt();
    int mx=0,pos=-1;
    rep(i,0,sz(st)){
      if(st[i].len > mx and st[i].cnt >= k){
        mx = st[i].len;
        pos = st[i].firstpos - mx + 1;
      }
    }
    return pii(pos,mx);
  }
  int PRE_WAYS=0;
  vi d;
  vi d2;
  void calc_ways(){
    if(PRE_WAYS)return;
    PRE_WAYS=1;
    calc_cnt();
    d.resize(sz(st));
    d2.resize(sz(st));
    vi id;

    rep(i,0,sz(st))id.pb(i);
    sort(all(id),[&](int a,int b){
      return st[a].len > st[b].len;
    });
    for(int i : id){
      d[i] = 1;
      d2[i] = st[i].cnt;
      rep(j,0,alpha){
        if(st[i].next[j]){
          d[i]+=d[st[i].next[j]];
          d2[i]+=d2[st[i].next[j]];
        }
      }
    }
  }
  string kth_not_repeat(int k){
    calc_ways();

    int p = 0;
    int some=1;
    string res="";
    k++;// empty
    while(some){
      some=0;
      if(k == 1)break;
      k--;
      rep(j,0,alpha){
        if(!st[p].next[j])continue;
        if(k > d[st[p].next[j]]){
          k-=d[st[p].next[j]];
        }else{
          res+=char(first + j);
          p = st[p].next[j];
          some=1;
          break;
        }
      }
    }
    return res;
  }
  string kth_repeat(int k){
    calc_ways();
    int p = 0;
    int some=1;
    string res="";
    while(some){
      some=0;
      
      if(p){
        if(k <= st[p].cnt)break;
        k-=st[p].cnt;
      }
      
      rep(j,0,alpha){
        if(!st[p].next[j])continue;
        if(k > d2[st[p].next[j]]){
          k-=d2[st[p].next[j]];
        }else{
          res+=char(first + j);
          p = st[p].next[j];
          some=1;
          break;
        }
      }
    }
    return res;
  }

};
