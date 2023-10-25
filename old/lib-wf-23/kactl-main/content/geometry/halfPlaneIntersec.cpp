/**
 * Author: UFPE
 * License: CC0
 * Description: Finds the half plane intersection. If can be unbounded/non-convex
 * May be useful to add a bounding box.
 * Status: Tested on BigBrother and Health in Hazard
 * Time: O(NlogN)
 */
#include "Point.h"
#include "lineIntersection.h"

typedef Point<double> P;

struct L {
    P a, b;
    double ang;
    L(){}
    L(P a, P b) : a(a), b(b) {}
    // reta para esquerda de a->b nessa ordem.
};
double angle (L la) { return atan2(-(la.a.y - la.b.y), la.b.x - la.a.x); }
const double inf = 1e100, eps = 1e-9;
const double PI = acos(-1.0L);
int cmp (double a, double b = 0) {
  if (abs(a-b) < eps) return 0;
  return (a < b) ? -1 : +1;
}
pair<int, P> lineInter(L la,L lb){
  return lineInter(la.a,la.b,lb.a,lb.b);
}
bool check (L la, L lb, L lc) {
    P p = lineInter(lb, lc).ss;
    double det = (la.b - la.a).cross(p - la.a);
    return cmp(det) < 0;
}
const int N = 500100;
int dq[2*N]; 
vector<P> hpi (vector<L> line) {
    rep(i,0,sz(line))line[i].ang = angle(line[i]);
    sort(line.begin(), line.end(), [&](L la,L lb){
        if (cmp(la.ang, lb.ang) == 0) return (lb.b - lb.a).cross(la.b - lb.a) > eps;
        return cmp(la.ang,lb.ang) < 0;
    });
    vector<L> pl(1, line[0]);
    rep(i,0,sz(line)) if (cmp(angle(line[i]), angle(pl.back())) != 0) pl.push_back(line[i]);
    int idl = N,idr = N;
    dq[idr++]=(0);
    dq[idr++]=(1);
    rep(i,2,sz(pl)) {
        while (idr - idl > 1 && check(pl[i], pl[dq[idr-1]], pl[dq[idr - 2]])) idr--;
        while (idr - idl > 1 && check(pl[i], pl[dq[idl]], pl[dq[idl+1]])) idl++;
        dq[idr++]=i;
    }
    while (idr - idl > 1 && check(pl[dq[idl]], pl[dq[idr-1]], pl[dq[idr - 2]])) idr--;
    while (idr - idl > 1 && check(pl[dq[idr-1]], pl[dq[idl]], pl[dq[idl + 1]])) idl++;
    vector<P> res;
    rep(i,idl,idr){
      int nxt = (i + 1 == idr ? idl : i+1);
      auto inter = lineInter(pl[dq[i]], pl[dq[nxt]]);
      if(inter.ff!=1){//non-convex
        res.clear();
        return res;
      }
      res.pb(inter.ss);
    }
    return res;
}
