/**
 * Author: Leal
 * Date: 2009-10-30
 * License: ??
 * Source: bit kth
 * Description: Pega o kth menor elemento que esta no BIT ou o Menor cara "j" tal que prefixo(j) >= K
 * Time: Both operations are $O(\log N)$.
 */
int bit[N];
 
void upd(int pos, int val){
    for(int i = pos; i < N; i += (i&-i)) bit[i] += val;
}
 
int kth(int x){
   int resp = 0;
    x--;
    for(int i = 20; i >= 0; i--){
        if(resp + (1<<i) >= N) continue;
        if(bit[resp + (1 << i)] <= x) 
            x -= bit[resp + (1 << i)], resp = resp + (1 << i);
    }
    return resp + 1;
}
