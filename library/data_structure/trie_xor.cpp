/* Trie for binary related problems
 * Author: NaimSS
 * Tested on CSES 1655
 * Assumes cnt is never NEGATIVE!
 * Useful ideas:
 * Smallest XOR / Biggest AND between all pairs: Two adjacent after sorting (also adjacent on trie)
 * Smallest OR : Take the smallest LOG + 1 items and bruteforce
 * Smallest AND / Biggest XOR / Biggest OR (????)
 * XOR-MST: Boruvka or D&C (look at /misc)
*/

// CAREFUL OVERFLOW AT 1<<i
const int N = ;
const int MAXL = ;
const int MX = N * MAXL;
int trie[MX][2];
int cnt[MX];
int nodes = 1;
void add(int x,int val = 1){
    int no = 1; // root
    cnt[no]+=val;
    for(int i=MAXL-1;i >= 0;i--){
        int b = x>>i&1;
        if(!trie[no][b])trie[no][b] = ++nodes;
        no = trie[no][b];
        cnt[no]+=val;
    }
}
int max_xor(int x){
    int no=1;
    int res=0;
    for(int i=MAXL-1;i>=0;i--){
        int b = x>>i&1;
        if(cnt[trie[no][b^1]])no = trie[no][b^1],res|=(1<<i);
        else no = trie[no][b];
    }
    return res;
}
