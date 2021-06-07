// resultados: 
/*
N: 1, divi: 1, num: 1
N: 10, divi: 4, num: 6
N: 100, divi: 12, num: 60
N: 1000, divi: 32, num: 840
N: 10000, divi: 64, num: 7560
N: 100000, divi: 128, num: 83160
N: 1000000, divi: 240, num: 720720
N: 10000000, divi: 448, num: 8648640
N: 100000000, divi: 768, num: 73513440
N: 1000000000, divi: 1344, num: 735134400
N: 10000000000, divi: 2304, num: 6983776800
N: 100000000000, divi: 4032, num: 97772875200
N: 1000000000000, divi: 6720, num: 963761198400
N: 10000000000000, divi: 10752, num: 9316358251200
N: 100000000000000, divi: 17280, num: 97821761637600
N: 1000000000000000, divi: 26880, num: 866421317361600
N: 10000000000000000, divi: 41472, num: 8086598962041600
N: 100000000000000000, divi: 64512, num: 74801040398884800
N: 1000000000000000000, divi: 103680, num: 897612484786617600
*/
void go(int pos,long long num,long long d,int lmax){
	
	if(d > cur || (d == cur && num < ans)){
		cur = d;
		ans = num;
	}
	
	if(lmax == 0) return;
	
	for(int i=1;i<=lmax;i++){
		if(num*pr[pos] > n) break;
		num *= pr[pos];
		go(pos+1,num,d*(i+1),i);
	}
 
}
 
main(){
	
	 freopen("divisors.in", "r", stdin);
   	 freopen("divisors.out", "w", stdout);
	cin >> n;
	int qnt = 0;
	
	for(int i=2;i<=200;i++)
		if(primo(i))
			pr[qnt++] = i;
		
	go(0,1,1,60);
}
