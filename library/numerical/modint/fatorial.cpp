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
