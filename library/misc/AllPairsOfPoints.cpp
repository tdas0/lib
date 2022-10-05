// Sort by distance to a line
// Useffull for finding area of triangles
// O(N^2logN)
// Source: https://codeforces.com/blog/entry/79928

typedef Point<ll> P;
const ll inf = 9e18;
struct coisa{
  P v;
  int id1,id2;
  coisa(P v,int id1,int id2):id1(id1),id2(id2),v(v){}
  bool operator<(const coisa &other)const{
    return v.cross(other.v) > 0;
  }
};

const int N = 2020;
int pos[N];

void solve(){
  int n;
  cin>>n;
  vector<P> p(n);
  for(int i=0;i<n;i++){
    cin >> p[i].x >> p[i].y;
  }
  
  sort(all(p),[&](P a,P b){ // sort by biggest Y
    return tie(a.y,a.x) > tie(b.y,b.x);
  });
  vector<coisa> aux;

  for(int i=0;i<n;i++){
    p[i].id = i;
    pos[i] = i;
  }
  for(int i=0;i<n;i++){
    for(int j=0;j<i;j++){
      aux.pb(coisa(p[j] - p[i],i,j));
    }
  }

  sort(all(aux));  
  
  for(auto c : aux){
    int id1 = c.id1,id2 = c.id2;
    int &a = pos[id1];
    int &b = pos[id2];
    assert(b == a-1);
    
    // [0...b-1] -> above line a->b
    // [a+1...n-1] -> below line a->b
   
    swap(p[a],p[b]);  
    swap(a,b);
  }
  cout << ans << endl;
}
