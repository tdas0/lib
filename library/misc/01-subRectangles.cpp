/**
 * Author: Naim
 * Source: http://www.deltami.edu.pl/temat/informatyka/algorytmy/2015/10/27/Zliczamy_puste_prostokaty/
 * Date: 2020-05-10
 * Description: acha a quantidade de retangulos de tamanho ixj sem obstaculos
 * '*' siginifica obstaculo e '.' lugar livre
 * Ideia parecida com a da maior area de um histograma
 * Time: O(N*M) , memory : O(N*M)
 * Status:tested on https://cses.fi/problemset/task/1148
 */

int n,m;
const int N = 1010; 
int c[N][N]; // c[i][j] == qtd de retangulos de tamanho i*j
char mat[N][N];
int d[N][N]; // maximo espaco pra cima
pii s[N];// ff-> h, ss->w // funciona como uma stack

void solve(){

  s[0] = pii(0,0);
  rep(i,0,n+2)rep(j,0,m+2)mat[i][j]='*';
  rep(i,1,n+1)rep(j,1,m+1)cin>>mat[i][j];

  rep(i,0,n+2)rep(j,0,m+2){
    if(i==0)d[i][j]=0;
    else d[i][j] = (mat[i][j]=='*'?0:d[i-1][j] + 1);
  }

 rep(i,1,n+1){
  int id=0,w,h;
    rep(j,0,m+2){
      w = 0;
      while(id>0 and s[id].ff >= d[i][j]){
        h = max(s[id-1].ff,d[i][j]);
        w +=s[id].ss;
        c[h+1][w]++;
        c[s[id].ff+1][w]--;
        id--;
      }
      id++;
      s[id] = pii(d[i][j],w+1);
    }
  
  }

// prefix sum
  rep(i,1,n+1){
    rep(j,1,m+1)c[i+1][j]+=c[i][j];
    per(j,1,m+1)c[i][j]+=c[i][j+1];
    per(j,1,m+1)c[i][j]+=c[i][j+1];
  }

// rep(i,1,n+1){rep(j,1,m+1){cout<<c[i][j]<<" ";}cout<<endl;}

}
