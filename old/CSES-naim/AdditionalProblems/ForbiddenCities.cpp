// queries de a,b,c
// dizer se todo caminho a->b passa por C
// grafo bidirecional
// n,m,q<=2e5
int is_ans(int a,int b){
	return (tin[a]<=tin[b] && tout[a]>=tout[b]);
}
 
int son(int a,int c){
	// maior ans de a que � filho de c;
	for(int i=19;i>=0;i--){
		if(ans[a][i]!=-1){
			if(!is_ans(ans[a][i],c))a = ans[a][i];
		}
	}
	return a;
}
	while(q--){
		int a,b,c;
		cin>>a>>b>>c;
		if(a==c || b==c){
			cout<<"NO"<<endl;
			continue;
		}
		int LCA = lca(a,b);
		if(LCA==c){
			int nva = son(a,c);
			int nvb = son(b,c);
			if(low[nva]<tin[c] && low[nvb]<tin[c]){
				cout<<"YES"<<endl;
			}else cout<<"NO"<<endl;
		}else if(h[LCA]>=h[c]){
			cout<<"YES"<<endl;
		}else{
			if(is_ans(c,b))swap(a,b);
			int nva = son(a,c);
			if(!is_ans(c,a) && !is_ans(c,b)){
				cout<<"YES"<<endl;
			}else if(low[nva]<tin[c]){
				cout<<"YES"<<endl;
			}else cout<<"NO"<<endl;
		}
		
	}