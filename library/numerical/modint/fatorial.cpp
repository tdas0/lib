/*
  fat[i] = (i*fat[i-1])
  inv[i] = (inv[i+1]*(i+1)) ou inv[i] = fat[i] ^ (phi(M) - 1)
  per_caotica[n] = (n-1)*(per_caotica[n-2] + per_caotica[n-1]) AKA Derangement
  !n = n * (!(n-1)) + (-1)^n para n>0
  per_caotica[n] = n! * sum(1/k! * (-1)^k)
  sum(C(n,k)*k) = n*2^(n-1) - prova: derivar binomio (1+x)^n em x = 1
*/

Mint  fat[N];
Mint inv[N];

Mint C(int n,int k){
  if(k > n || k<0)return Mint(0);
  return fat[n]*inv[k]*inv[n-k];
}

void init(){//checar maxN
  fat[0] = inv[0] = 1;
  for(int i=1;i<N;i++)
    fat[i] = i*fat[i-1];
  inv[N-1] = 1/fat[N-1];
  for(int i=N-2;i>=0;i--)inv[i]=(i+1)*inv[i+1];
}
