/**
 * Author: dadalto
 * Description: Min-Cost Max-Flow: O(V^2E^2).
 * Vertices are labeled from 0 to n (inclusive).
 * Edge cost and capacities must fit int (flow and cost 
 * returned are long long).
 * Edge cost in network must not create an negative cost cycle		
 * Call mincost_maxflow to get the total flow and its cost (in this order). 
 * Individual edge flows can be retrieved in the graph. 
 * Note that flow will be negative in return edges.
 * Time: O(V^2E^2).
 */
namespace mcmf
{
struct edge
{
	int dest, cap, re, cost, flow;
};

const int MAXV = 112345;
const ll infll = 0x3f3f3f3f3f3f3f3fLL;
const int inf = 0x3f3f3f3f;

int n, s, t, p[MAXV], e_used[MAXV];
bool in_queue[MAXV];
ll d[MAXV];

vector<vector<edge>> graph;

void init(int _n, int _s, int _t)
{
	n = _n, s = _s, t = _t;
	graph = vector<vector<edge>>(n + 1);
}

void put_edge(int u, int v, int cap, int cost)
{
	graph[u].push_back({v, cap, (int)graph[v].size(), cost, 0});
	graph[v].push_back({u, 0, (int)graph[u].size() - 1, -cost, 0});
}

bool spfa()
{
	memset(in_queue, 0, sizeof(bool) * (n + 1));
	memset(d, 0x3f, sizeof(ll) * (n + 1));
	queue<int> q;
	d[s] = 0;
	p[s] = s;
	q.push(s);
	while (!q.empty())
	{
		int a = q.front();
		q.pop();
		in_queue[a] = false;

		for (int i = 0; i < graph[a].size(); i++)
		{
			edge &e = graph[a][i];
			if (e.cap - e.flow > 0 && d[e.dest] > d[a] + e.cost)
			{
				d[e.dest] = d[a] + e.cost;
				p[e.dest] = a;
				e_used[e.dest] = i;
				if (!in_queue[e.dest])
					q.push(e.dest);
				in_queue[e.dest] = true;
			}
		}
	}

	return d[t] < infll;
}

pll mincost_maxflow()
{
	pll retv = pll(0, 0);
	while (spfa())
	{
		int x = inf;
		for (int i = t; p[i] != i; i = p[i])
			x = min(x, graph[p[i]][e_used[i]].cap - graph[p[i]][e_used[i]].flow);
		for (int i = t; p[i] != i; i = p[i])
			graph[p[i]][e_used[i]].flow += x, graph[i][graph[p[i]][e_used[i]].re].flow -= x;

		retv.first += x;
		retv.second += x * d[t];
	}

	return retv;
}
} // namespace mcmf
