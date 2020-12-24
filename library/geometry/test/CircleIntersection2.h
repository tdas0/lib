// menos impreciso ? idk tested on ASC4
bool eq(ld a,ld b){
  return abs(a-b)<=EPS;
} 
typedef Point<ld> P;
 
 
vector<P> circleInter(P a,P b,ld r1,ld r2) {
  vector<P> res;
  
  P vec = b - a;
 
  ld d = vec.dist();
  if(d>r1 + r2 || d + min(r1,r2) < max(r1,r2))return res;
  
  ld x = (d*d - r2*r2 + r1*r1)/(2*d);
  ld y = sqrt(r1*r1 - x*x);
  P v = (b-a)/d;
  res.pb(a + v*x + v.perp()*y);
  if(y>0){
    res.pb(a+ v*x - (v.perp())*y);
  }
  return res;
}
