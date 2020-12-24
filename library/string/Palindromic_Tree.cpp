/* Palindromic Tree, tree[1] são os nós impares, tree[2] são os nós pares, oc é a quantidade de ocorrencia e len o tamanho do palindromo
link é a maior substring palindromic que é sufixo do nó atual */
const int N = 300005;
int bigsuf , id;
struct node{
  int link , len , oc = 0;
  vi go;
} tree[N];

string s;
void init(){
  bigsuf = 2 , id = 2;
  tree[1].link = 1 , tree[1].len = -1 , tree[1].go = vi(26);
  tree[2].link = 1 , tree[2].len = 0 , tree[2].go = vi(26);
}

void append(int p){
  int c = s[p] - 'a' , cur = bigsuf;
  while((p - tree[cur].len - 1) < 0 || s[p-tree[cur].len-1] != s[p])
    cur = tree[cur].link;
  if(!tree[cur].go[c]){
    int link = tree[cur].link;
    while((p - tree[link].len - 1) < 0 || s[p-tree[link].len-1] != s[p])
      link = tree[link].link;		
    tree[cur].go[c] = ++id;
    tree[id].len = tree[cur].len + 2;
    tree[id].link = (tree[id].len == 1 ? 2 : tree[link].go[c]);
    tree[id].go = vi(26);
  }
  tree[tree[cur].go[c]].oc++;
  bigsuf = tree[cur].go[c];
}
