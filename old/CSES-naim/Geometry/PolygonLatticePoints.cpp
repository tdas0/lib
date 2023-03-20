/*
Print two integers: the number of lattice points inside the 
polygon and on its boundary.
*/
int n;
cin >> n;
vector<P> p(n+1);
rep(i,0,n)p[i].r();

ll area=0;
rep(i,0,n-1)area+=p[0].cross(p[i],p[i+1]);
area = abs(area);
int bound=0;
p[n] = p[0];
rep(i,0,n){
P a = p[i];
P b = (p[i+1]);
int dx = abs(a.x - b.x);
int dy = abs(a.y - b.y);
bound+=gcd(dx,dy);
}
// pick
// area * 2 == int * 2 + bound - 2
// i
int i = area - bound + 2;
cout << i/2 <<" "<<bound<<endl;