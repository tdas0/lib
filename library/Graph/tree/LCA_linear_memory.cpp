/*
 * Source: https://codeforces.com/blog/entry/74847
 * Complexity:
 *  Build: O(N)
 *  Query: Around 3*log(N) = O(log(N))
 *  Memory: O(N)
 * Tested on CSES and https://codeforces.com/problemset/problem/1702/G2
 * Benchmarking on CSES:
 * RMQ (O(N\logN build)) -> 0.31s
 * Standart -> 0.51s
 * This one -> 0.39s
*/
const int N = ;
int H[N],jmp[N],pai[N];

int find(int v,int d){//go up to depth d
    while(H[v] > d){
        if(H[jmp[v]] < d){
            v = pai[v];
        }else v = jmp[v];
    }
    return v;
}

int lca(int a,int b){
    if(H[a] < H[b])
        swap(a,b);
    a = find(a,H[b]);
    while(a!=b){
        if(jmp[a] == jmp[b]){
            a=pai[a];
            b=pai[b];
        }else{
            a=jmp[a];
            b=jmp[b];
        }
    }
    return a;
}
int dist(int a,int b){
    return H[a] + H[b] - 2*H[lca(a,b)];
}

// find first vertice in anscestory to have something binary_searchable
// O(log(N))
/*int search(int v){ 
    while(!test(v)){
        if(test(jmp[v]))
            v = pai[v];
        else
            v = jmp[v];
    }
}*/

void makeLeaf(int v,int p){
    pai[v] = p;
    H[v] = H[p] + 1;
    if(H[p] - H[jmp[p]] == H[jmp[p]] - H[jmp[jmp[p]]]){
        jmp[v] = jmp[jmp[p]];
    }else{
        jmp[v] = p;
    }
}

vi g[N];
void dfs(int v,int p = -1){
    if(p==-1){
        jmp[v] = v;
        H[v] = pai[v] = 0;
    }else{
        makeLeaf(v,p);
    }

    for(auto to : g[v])if(to!=p){
        dfs(to,v);
    }
}
