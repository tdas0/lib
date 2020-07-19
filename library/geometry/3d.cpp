/* Some things to solve 3d geometry problems
 * Source: KACTL lib + Um_nik
 * Status: Tested on https://codeforces.com/gym/102040/attachments problem I
*/
typedef long double ld;
template<class T> struct Point3D {
  typedef Point3D P;
  typedef const P& R;
  T x, y, z;
  explicit Point3D(T x=0, T y=0, T z=0) : x(x), y(y), z(z) {}
  int read(){ // read faster than long double
    int x;
    cin >> x;
    return x;
  }
  void scan(){
    x = read(),y=read(),z=read();
  }
  bool operator<(R p) const {
    return tie(x, y, z) < tie(p.x, p.y, p.z); }
  bool operator==(R p) const {
    return tie(x, y, z) == tie(p.x, p.y, p.z); }
  P operator+(R p) const { return P(x+p.x, y+p.y, z+p.z); }
  P operator-(R p) const { return P(x-p.x, y-p.y, z-p.z); }
  P operator*(T d) const { return P(x*d, y*d, z*d); }
  P operator/(T d) const { return P(x/d, y/d, z/d); }
  T dot(R p) const { return x*p.x + y*p.y + z*p.z; }
  P cross(R p) const {
    return P(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);
  }
  T dist2() const { return x*x + y*y + z*z; }
  ld dist() const { return sqrt((ld)dist2()); }
  //Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
  double phi() const { return atan2(y, x); } 
  //Zenith angle (latitude) to the z-axis in interval [0, pi]
  double theta() const { return atan2(sqrt(x*x+y*y),z); }
  P unit() const { return *this/(T)dist(); } //makes dist()=1
  //returns unit vector normal to *this and p
  P normal(P p) const { return cross(p).unit(); }
  //returns point rotated 'angle' radians ccw around axis
  P rotate(double angle, P axis) const {
    double s = sin(angle), c = cos(angle); P u = axis.unit();
    return u*dot(u)*(1-c) + (*this)*c - cross(u)*s;
  }
    friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << p.x << "," << p.y <<","<<p.z<< ")"; }
};
typedef Point3D<ld> P;
const ld EPS = 1e-8;


P ProjectionOnPlane(P p,P o,P n){ // plane has normal n and a point o
  n = n.unit();
  return p + n*(n.dot(o-p));
}


P ProjectionOnLine(P p,P o,P d){//origem em o e vetor diretor d
  d = d.unit();
  return o + d*(d.dot(p - o));
}

bool onSegm(P a,P b,P c){
  ld val = (a-b).dot(c-b);
  return val < 0 || abs(val)<=EPS;
}

ld PointSegDist(P a,P p,P q){
  P proj = ProjectionOnLine(a,p,q-p);
  if(onSegm(p,proj,q))return (a-proj).dist();
  return min((a-p).dist(),(a-q).dist());
}

bool intersectLinePlane(P p,P q,P o,P n,P &I){ // line p->q, plane o,n
  P d = q-p;
  if(abs(d.dot(n))<=EPS)return false;
  ld t = ((o-p).dot(n))/d.dot(n);
  I = p + d*t;
  return true;
}

ld SegSegDist(P a,P b,P c,P d){
  ld res = min(min(PointSegDist(a,c,d),PointSegDist(b,c,d))
              ,min(PointSegDist(c,a,b),PointSegDist(d,a,b)));
  P n = (b-a).cross(d-c);
  if(abs(n.dist())<=EPS)return res;
  n = n.unit();
  P I1,I2;
  if(!intersectLinePlane(a,b,c,(d-c).cross(n),I1))throw;
  if(!intersectLinePlane(c,d,a,(b-a).cross(n),I2))throw;
  if(!onSegm(a,I1,b))return res;
  if(!onSegm(c,I2,d))return res;
  return min(res,(ld)(I1-I2).dist());
}

bool inTriang(P p, vector<P> t) {
  ld S = 0;
  S += ((t[1] - t[0]).cross(t[2] - t[0])).dist();
  for (int i = 0; i < 3; i++){
    S -= ((t[i] - p) .cross(t[(i + 1)%3] - p)).dist();
  }
  return abs(S)<=EPS;
}
