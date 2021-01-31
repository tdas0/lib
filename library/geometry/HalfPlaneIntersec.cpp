/**
 * Source: Lib do Gabriel Pessoa
 * Status: Testado no "big brother" apenas...
**/
#include "Point.h"
#include "lineIntersection.h"

typedef Point<double> P;
typedef Point<double> PT;

struct L {
    PT a, b;
    double ang;
    L(){}
    L(PT a, PT b) : a(a), b(b) {}
};

double angle (L la) { return atan2(-(la.a.y - la.b.y), la.b.x - la.a.x); }

const double inf = 1e100, eps = 1e-9;
const double PI = acos(-1.0L);

int cmp (double a, double b = 0) {
  if (abs(a-b) < eps) return 0;
  return (a < b) ? -1 : +1;
}

bool comp (L la, L lb) {       
    if (cmp(la.ang, lb.ang) == 0) return (lb.b - lb.a).cross(la.b - lb.a) > eps;
    return cmp(la.ang,lb.ang) < 0;
}


pair<int, PT> lineInter(L la,L lb){
  return lineInter(la.a,la.b,lb.a,lb.b);
}

bool check (L la, L lb, L lc) {
    PT p = lineInter(lb, lc).ss;
    double det = (la.b - la.a).cross(p - la.a);
    return cmp(det) < 0;
}


const int N = 500100;
int dq[2*N]; // pode substituir por um deque normal
int idl,idr; // idr++ -> push_back, idr-- (popback), idl++(popfront)

// pi->pj - esquerda
// NAO FUNCIONA NEM FOI TESTADO SE NAO RETORNAR ALGO CONVEXO

vector<PT> hpi (vector<L> line) { // salvar (i, j) CCW, (j, i) CW
    rep(i,0,sz(line))line[i].ang = angle(line[i]);
    sort(line.begin(), line.end(), comp);
    vector<L> pl(1, line[0]);
    for (int i = 0; i < (int)line.size(); ++i) if (cmp(angle(line[i]), angle(pl.back())) != 0) pl.push_back(line[i]);
    idl = N,idr = N;
    dq[idr++]=(0);
    dq[idr++]=(1);
    for (int i = 2; i < (int)pl.size(); ++i) {
        while (idr - idl > 1 && check(pl[i], pl[dq[idr-1]], pl[dq[idr - 2]])) idr--;
        while (idr - idl > 1 && check(pl[i], pl[dq[idl]], pl[dq[idl+1]])) idl++;
        dq[idr++]=i;
    }
    while (idr - idl > 1 && check(pl[dq[idl]], pl[dq[idr-1]], pl[dq[idr - 2]])) idr--;
    while (idr - idl > 1 && check(pl[dq[idr-1]], pl[dq[idl]], pl[dq[idl + 1]])) idl++;
    vector<PT> res;
    for (int i = 0; i < idr - idl; ++i){
      int nxt = (idl + i + 1 == idr ? idl : idl + i+1);
      auto IT = lineInter(pl[dq[idl + i]], pl[dq[nxt]]);
      if(IT.ff!=1){ // Nao retorna uma area convexa
        res.clear();
        return res;
      }
      res.pb(IT.ss);
    }
    return res;
}
