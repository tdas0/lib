/* Count number of points in Left and Right of the Line
 * No Collinears and without including the line
 * Prefix sum if the Points have values is a good ideia
 * And maybe double the  vector to avoyd %n
 * https://codeforces.com/contest/1284/problem/E
 */
ll go(vector<P> pts){

  sort(all(pts) , [&](P a , P b){
    
    int hp1 = a < P(0,0),hp2 = b<P(0,0);

    if(hp1 != hp2) return hp1 < hp2;
    if(a.cross(b) != 0){
      return a.cross(b)  > 0;
    }
    return a.dist2() < b.dist2();
  });

  int n =pts.size();
  int j=0;
  ll ans = 0;
  rep(i,0,n){
      while(j < i + n and pts[i].cross(pts[j%n])>=0)j++;
      ll left = j-i-1; // (dont include the line)
      // update answer
  }

  return ans;

}
