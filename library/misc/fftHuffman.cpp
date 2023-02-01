// acha produto de muitos polinomios simulando huffman
// slow but easy to code
// https://codeforces.com/contest/1096/submission/81631914
// https://codeforces.com/contest/1257/submission/81425688

struct cmp{
 bool operator()(const vl& a,const vl& b) const {
  return sz(a) < sz(b);
 }
};

int main(){

  multiset<vl, cmp > S;

  const int M = 998244353;
  while(S.size() > 1){
    auto it = S.begin();
    auto it2 = it;
    it++;
    S.insert(convMod<M>(*it,*it2));
    S.erase(it);S.erase(it2);
  }
  vl res = *S.begin();
}
