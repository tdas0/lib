#include "../flow/dinic/dinic.cpp"

/*
  ** Muda o Dinic pro do KACTL, é fácil adaptar depois disso ** 
	Gomory-Hu Tree construction O(V * flow_time) (so O(V^3E), but not 
	really):
		The Gomory-Hu tree of an undirected graph with capacities is a 
		weighted
		tree that represents the minimum s-t cuts for all s-t pairs in 
		the graph.
		The minimum cut cost between vertices s and t is the minimum 
		cost of an edge on the path from s to t in the Gomory-Hu tree.
	Constraints:
		Vertices are labeled from 0 to n-1 (inclusive).
		Undirected graph.
	Usage:
		Check Dinic usage.
		Create struct and call add edge for each edge in the graph.
		Then, just call solve passing the number of vertices.
		The vector returned will have size n and for each i > 0,
		retv[i] is a pair (cost, parent) representing an edge 
		(i, parent) in the Gomory-Hu tree.
		retv[0] means nothing.
*/

struct gomory_hu
{
	struct edg
	{
		int u, v, cap;
	};

	vector<edg> edgs;

	void add_edge(int u, int v, int cap)
	{
		edgs.push_back({u, v, cap});
	}

	vector<int> vis;

	void dfs(int a)
	{
		if (vis[a])
			return;
		vis[a] = 1;
		for (auto &e : dinic::graph[a])
			if (e.cap - e.flow > 0)
				dfs(e.dest);
	}

	vector<pair<ll, int>> solve(int n) 
	{					   
		vector<pair<ll, int>> retv(n); // if i > 0, stores pair(cost, 
									   // parent).
		for (int i = 1; i < n; i++)
		{
			dinic::init(n, i, retv[i].second);

			for (auto &e : edgs)
				dinic::put_edge_undirected(e.u, e.v, e.cap);

			retv[i].first = dinic::max_flow();
			
			vis.assign(n, 0);
			dfs(i);

			for (int j = i + 1; j < n; j++)
				if (retv[j].second == retv[i].second && vis[j])
					retv[j].second = i;
		}

		return retv;
	}
};
