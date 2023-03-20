/**
 * Author: Matheus Leal
 * Date: ??-??-??
 * License: ??
 * Source: own work
 * Description: Faz todas as operacoes em O(1) armotizado, porem eh necessario que
 * os coeficientes angulares das retas estejam ordenados (decrescente) na ordem que insere, assim como os "x" das queries (crescente)
 * Time: O(N) total, O(1) por query
 * Tested on https://codeforces.com/contest/1715/problem/E
 * Status: stress-tested
 */

struct cht {
    int p = 0;
    vector<pii> func;
    //Cuidado com OVERFLOW
    bool bad(pii A, pii B, pii C){
    return (ll)(B.s - A.s)*(A.f - C.f) > (ll)(C.s - A.s)*(A.f - B.f);
    }
    ll f(pii r, ll x){
        return r.f*x + r.s;
    }
    void addline(pii r) {
        if(!func.empty() and func.back().f == r.f){
            if(func.back().s <= r.s) return;
            func.pop_back();
            if(p == sz(func)) p--;
        }
        while(func.size() >= 2 && bad(func[sz(func) - 2], func[sz(func) - 1], r)){
            func.pop_back();
            if(p == sz(func)) p--;
        }
        func.push_back(r);
    }
    ll queryMin(ll x){
        assert(!func.empty());
        assert(p < sz(func));
        while(p < sz(func) - 1 && f(func[p], x) > f(func[p + 1], x)) p++;
        return f(func[p], x);
    }

};
