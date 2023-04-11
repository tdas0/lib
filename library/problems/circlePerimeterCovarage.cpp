/*
 * Can be used to find if there is a point in the permiter a circle that is 
 * not in any other circle. Also useful to checking if a collection of angles
 * covers the hole 2PI circle. 
 * tested on Gena and second distance: https://codeforces.com/contest/442/problem/E
*/
typedef Point<ld> P;
vector<P> vec;
int w,h,n;

const double eps = 1e-9,PI = acos(-1);

struct event{
  ld x;
  int add;
  int id;
};

ld normalize(ld ang){
  while(ang <= -PI+eps)ang+=2*PI;
  while(ang > PI+eps)ang-=2*PI;
  return ang;
}
vector<event> ev;
void add_ev(ld L,ld R,int v,int id){
  ev.pb({L,v,id}),ev.pb({R,-v,id});
}
void insert_ev(double mid,double dif,int peso,int id){
  if(isnan(dif))return;
  ld L = normalize(mid - dif);
  ld R = normalize(mid + dif);
  add_ev(L,R,peso,id);
}

int ok(int id,double R){
  // checar se tem algum ponto na fronteira de (vec[id],R) que nao esteja em outro circulo
  // (vec[j],R).
  ev.clear();
  rep(i,0,n)if(i!=id){
    P delta = (vec[i] - vec[id]);
    ld dx = delta.x,dy=delta.y,dist=delta.dist();
    if(dist<=eps)continue;
    insert_ev(atan2(dy,dx),acos(dist/2/R),+1,i);
  }

  { // muros
    // cima
    insert_ev(PI/2,acos(fabs(h - vec[id].y)/R),+2,n);
    // baixo
    insert_ev(-PI/2,acos(fabs(vec[id].y)/R),+2,n+1);
    // dir
    insert_ev(0,acos(fabs(w - vec[id].x)/R),+2,n+2);
    // esq
    insert_ev(PI,acos(fabs(vec[id].x)/R),+2,n+3);
  }

  // time to sweep like a sir
  sort(all(ev),[&](event a,event b){
    if(fabs(a.x - b.x) > eps)return a.x < b.x;
    return a.add > b.add;
  });
  int act=0;
  vector<int> vis(n+10,0);
  auto upd = [&](event e){
    if(e.add > 0){
      act+=e.add;
      vis[e.id]=1;
    }else if(vis[e.id]){
      vis[e.id]=0;
      act+=e.add;
    }
  };

  for(auto e : ev){ // primeiro apenas coloca todo mundo
    upd(e);
  }
  if(act < 2)return 1;// ja ta ok

  for(auto e : ev){
    upd(e); // coloca ou tira evento
    if(act<2)return 1;
  }
  return 0;
}
