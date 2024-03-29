// build O(N),busca lixo kkk
// menor cara é a raiz, L[i] e R[i] são os filhos (menores após excluir o pai no range)

	int root = 0;
	for(int i=1;i<=n;i++){
			int ant = i-1;
			while(ant!=0 and val[ant] > val[i]){
				ant = pai[ant];
			}
			if(ant){
				pai[i] = ant;
				L[i] = R[ant];
				pai[L[i]] = i;
				R[ant] = i;
			}else{
				pai[i] = 0;
				L[i] = root;
				pai[root] = i;
				root = i;
			}
			
	}
	pai[root] = root;
