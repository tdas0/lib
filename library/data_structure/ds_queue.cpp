/**
 * Author: Tiago
 * Source: https://codeforces.com/blog/entry/83467
 * Description: Permite remover os upds de uma estrutura de dados como uma queue
 * Requisitos: 
 * A estrutura deve permitir rollback (retirar o último update feito)
 * A estrutura é comutativa, ou seja, o resultado de uma query independe da ordem dos updates que estão presentes
 * Uso:
 * Passe a estrutura DS no add e undo, DS deve ter
 * DS.push() recebe um update e trata ele na estrutura
 * DS.pop() desfaz o update mais antigo que ainda está presente na estrutura
 * push(U, DS) adiciona um update no fundo da ds_queue
 * pop(DS) remove um update da frente da ds_queue
 * Time: O(Nlog(N)*(A + B)) onde A/B é o tempo de fazer/desfazer um update na esturtura
 * Status: tested in cf
 */
template<class U>
class ds_queue{
public:
	void push(U upd , auto &DS){
		Q.push_back({upd, 1});
		DS.push(upd);
	}
	void pop(auto &DS){
		if(!sz(Q))
			return;
		if(Q.back().S){
			vector< pair< U , bool> > block[2];
			do{
				block[Q.back().S].push_back(Q.back());
				Q.pop_back() , DS.pop();
			} while(sz(block[0]) != sz(block[1]) && sz(Q));
			if(!sz(block[0])){
				for(auto & w : block[1])
					w.S = 0 , DS.push(w.F);
				swap(Q,block[1]);
			}
			else{
				for(int j = 1; j >= 0 ; j --){
					while(sz(block[j])){
						auto w = block[j].back();
						block[j].pop_back();
						Q.push_back(w) , DS.push(w.F);
					}
				}
			}
		}
		DS.pop() , Q.pop_back();
	}
private:
	vector < pair< U , bool> > Q;
};
