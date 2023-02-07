/*
 * Acha a solucao de a*x+b*y=c com x>=0,y>=0 e y menor possivel
 * Teoremas uteis aqui: McChicken
 * Status: Tested on https://codeforces.com/contest/1728/problem/E
 */

int gcd(int a, int b, ll & x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    int d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

bool find_any_solution(int a, int b, int c, ll &x0, ll &y0, int &g) {
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }
    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

// assumes a,b coprime (if not in input divide by gcd)
void shift_solution(ll & x, ll & y, ll a, ll b, ll cnt) {
    x += cnt * b;
    y -= cnt * a;
}

void shift_y(ll &x,ll &y ,int a,int b){
	if(y<0){
		ll need = (abs(y)+a-1)/a;
		shift_solution(x,y,a,b,-need);
	}else{
		shift_solution(x,y,a,b,y/a);
	}
}
// sol of a*x0 + b*y0 = c where y0 is the smallest with y0>=0
bool find_any_solution_positive(int a,int b,int c,ll &x0,ll  &y0, int & g){
	if(!find_any_solution(a,b,c,x0,y0,g)){
		return false;
	}
	shift_y(x0,y0,a/g,b/g);
  if(x0<0)return false;
	return true;
}
