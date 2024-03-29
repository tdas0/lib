/**
 * Author: chilli, Takanori MAEHARA
 * Date: 2019-05-10
 * License: CC0
 * Source: https://github.com/spaghetti-source/algorithm/blob/master/graph/arborescence.cc
 * Description: Edmonds' algorithm for finding the weight of the minimum spanning
 * tree/arborescence of a directed graph, given a root node. If no MST exists, returns -1.
 * For Ununroteed you can add a virtual node to everyone with cost infinity.
 * DOES NOT STORE THE EDGES OF TREE
 * Time: O(E \log V)
 * Status: Stress-tested, also tested on NWERC 2018 fastestspeedrun
 */
#pragma once

#include "dsu.cpp"

struct Edge { int a, b; ll w; };
struct Node { /// lazy skew heap node
	Edge key;
	Node *l, *r;
	ll delta;
	void prop() {
		key.w += delta;
		if (l) l->delta += delta;
		if (r) r->delta += delta;
		delta = 0;
	}
	Edge top() { prop(); return key; }
};
Node *merge(Node *a, Node *b) {
	if (!a || !b) return a ?: b;
	a->prop(), b->prop();
	if (a->key.w > b->key.w) swap(a, b);
	swap(a->l, (a->r = merge(b, a->r)));
	return a;
}
void pop(Node*& a) { a->prop(); a = merge(a->l, a->r); }

ll dmst(int n, int r, vector<Edge>& g) {
	dsu uf(n);
	vector<Node*> heap(n);
	trav(e, g) heap[e.b] = merge(heap[e.b], new Node{e});
	ll res = 0;
	vi seen(n, -1), path(n);
	seen[r] = r;
	rep(s,0,n) {
		int u = s, qi = 0, w;
		while (seen[u] < 0) {
			path[qi++] = u, seen[u] = s;
			if (!heap[u]) return -1;
			Edge e = heap[u]->top();
			heap[u]->delta -= e.w, pop(heap[u]);
			res += e.w, u = uf.find(e.a);
			if (seen[u] == s) {
				Node* cyc = 0;
				do cyc = merge(cyc, heap[w = path[--qi]]);
				while (uf.join(u, w));
				u = uf.find(u);
				heap[u] = cyc, seen[u] = -1;
			}
		}
	}
	return res;
}
