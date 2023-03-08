// completar grid com A,B
// cada linha/col com exatamente um A/B
	int n;
	cin >> n;
	int A=n,B=n;
	rep(i,0,n){
		rep(j,0,n){
			cin >> mat[i][j];
			if(mat[i][j] == 'A'){
				tem[i][j+n] = 1;
				in[j+n]++;
				out[i]++;
				A--;
			}else if(mat[i][j] == 'B'){
				tem[j+n][i] = 1;
				in[i]++;
				out[j+n]++;
				B--;
			}
		}
	}
	
	int badA=0,badB=0;
	rep(i,0,n)rep(j,n,2*n){
		if(tem[i][j]){
			if(in[i] == 0 && out[j]==0)badA++;
		}
		if(tem[j][i]){
			if(in[j] == 0 && out[i] == 0)badB++;
		}
	}
	int isoA=0,isoB=0;
	rep(i,0,n){
		if(in[i]+out[i]==0){
			isoA++;
		}
	}
	rep(j,n,2*n){
		if(in[j] + out[j]==0)isoB++;
	}
 
	for(int a=0;a<=badA;a++){
		for(int b=0;b<=badB;b++){
			for(int iso=0;iso<=min(isoA,isoB);iso++){
				// juntar os pares badA:
				ll ways = C[badA][a];
				ways = ways * (ll)C[badB][b]%M; // juntar os bads de B
				// juntar os singles:
				ll singles = C[isoA][iso]%M*C[isoB][iso]%M*fat[iso]%M;
				ways = ways * singles%M;
				int cA = A-b-iso,cB = B-a-iso;
				ways = ways * fat[cA]%M * fat[cB]%M;
				(dp[(a + b  + iso)]+=ways)%=M;
			}
		}
	}
	ll res=0;
	for(int i=0;i<=n;i++){
		res += ((i%2 == 0 ? 1 : -1) * dp[i]);
	}
	res%=M;
	if(res<0)res+=M;
 
	cout << res << endl;
