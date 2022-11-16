/**
  * Author: Naim
  * Source: https://codeforces.com/blog/entry/85900
  * Status: Tested on https://codeforces.com/gym/103466/problem/I
  * Description: Hash for a set or multiset. Overflow on purpose :)
  * Another option is to make hash = xor val[i][freq[i]]; if the max
  * Frequency is small. Usefull for replacing map<vector,T> -> map<ull,T>
  */
std::mt19937_64 rng64((int) std::chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;
ull val[MAX];
void init(){
  rep(i,0,MAX)val[i] = rng64();
}

ull getHash(vector<int>& vec){
  ull h=0;
  for(auto v : vec)h+=val[v];// xor for set
  return h;
}
