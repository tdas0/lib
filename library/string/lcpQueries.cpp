#include "../data_structure/RMQ.h"
// WATCH OUT! If lcp[i] = lcp(sa[i-1],sa[i]) this works.
// If lcp[i] = lcp(sa[i],sa[i+1]) then query should be:
// [min,max-1]

struct SuffixArray {
	vi sa, lcp;
	SuffixArray(string& s, int lim=256) {
		// ....
     init();
	}
    RMQ<int> rmq;
    vi rank;
    void init(){
        rmq.init(lcp);
        rank = vi(sz(sa));
        rep(i,0,sz(sa))rank[sa[i]] = i;
    }
    int query(int i,int j){//lcp for suffixes s[i...] and s[j...]
        if(max(i,j)>=sz(sa))return 0; // usually not needed
        if(i == j)return sz(sa)-1-i;
        return rmq.query(min(rank[i],rank[j])+1,max(rank[i],rank[j]));
    }
};
