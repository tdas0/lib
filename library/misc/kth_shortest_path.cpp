
/**
 * Author: tdas
 * Date: ???-??-??
 * License: CC0
 * Source: own work
 * Description: Get kth shortest path in directed graph
 * 1 <= N,M <= 300000
 * 1 <= K <= 300000
 * 0 <= s,t < N
 * 0 <= u,v < N
 * 0 <= ci <= 1e7
 * Time: O((K+M)\log N)
 * Status: stress-tested
 */

std::mt19937 mt(48);

template <typename T>
struct heap_node {
    std::array<heap_node*, 2> c;
    T key;

    friend heap_node* insert(heap_node* a, T new_key) {
        if (!a || new_key.first < a->key.first) {
            heap_node* n = new heap_node;
            n->c = {a, nullptr};
            n->key = new_key;
            return n;
        }
        a = new heap_node(*a);
        int z = mt() & 1;
        a->c[z] = insert(a->c[z], new_key);
        return a;
    }
};

template <typename T> using min_priority_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;

std::vector<int64_t> k_shortest_paths(int N, std::vector<std::pair<std::array<int, 2>, int64_t>> edges, int st, int en, int K) {
    int M = int(edges.size());

    std::vector<std::vector<std::tuple<int, int, int64_t>>> radj(N);
    for (int e = 0; e < M; e++) {
        auto [x, l] = edges[e];
        auto [u, v] = x;
        radj[v].push_back({e, u, l});
    }

    std::vector<int64_t> dist(N, -1);
    std::vector<int> prvE(N, -1);
    std::vector<int> toposort; toposort.reserve(N);

    {
        min_priority_queue<std::pair<int64_t, int>> q;
        q.push({dist[en] = 0, en});

        while (!q.empty()) {
            auto [d, cur] = q.top(); q.pop();
            if (d > dist[cur]) continue;
            toposort.push_back(cur);
            for (auto [e, nxt, l] : radj[cur]) {
                if (dist[nxt] == -1 || d + l < dist[nxt]) {
                    prvE[nxt] = e;
                    q.push({dist[nxt] = d + l, nxt});
                }
            }
        }
    }

    std::vector<std::vector<std::pair<int64_t, int>>> adj(N);
    for (int e = 0; e < M; e++) {
        auto& [x, l] = edges[e];
        const auto& [u, v] = x;
        if (dist[v] == -1) continue;
        assert(dist[u] != -1);

        l += dist[v] - dist[u];
        assert(l >= 0);

        if (e == prvE[u]) continue;

        adj[u].push_back({l, v});
    }
    for (int i = 0; i < N; i++) {
        sort(adj[i].begin(), adj[i].end());
        adj[i].push_back({-1, -1}); // Sentinel
    }

    using iter_t = decltype(adj[0].begin());
    using hnode = heap_node<std::pair<int64_t, iter_t>>;
    std::vector<hnode*> node_roots(N, nullptr);
    for (int cur : toposort) {
        if (cur != en) {
            assert(edges[prvE[cur]].first[0] == cur);
            int prv = edges[prvE[cur]].first[1];
            node_roots[cur] = node_roots[prv];
        } else {
            node_roots[cur] = nullptr;
        }

        const auto& [l, nxt] = adj[cur][0];
        if (nxt != -1) {
            node_roots[cur] = insert(node_roots[cur], {l, adj[cur].begin()});
        }
    }

    std::vector<std::pair<int64_t, int>> dummy_adj({{0, st}, {-1, -1}});

    std::vector<int64_t> res; res.reserve(K);
    min_priority_queue<std::tuple<int64_t, hnode*, iter_t>> q;
    q.push({dist[st], nullptr, dummy_adj.begin()});
    while (int(res.size()) < K && !q.empty()) {
        auto [l, start_heap, val_iter] = q.top(); q.pop();
        res.push_back(l);
        int64_t elen = val_iter->first;
        if (next(val_iter)->second != -1) {
            q.push({l - elen + next(val_iter)->first, nullptr, next(val_iter)});
        }
        if (start_heap) {
            for (int z = 0; z < 2; z++) {
                auto nxt_start = start_heap->c[z];
                if (!nxt_start) continue;
                q.push({l - elen + nxt_start->key.first, nxt_start, nxt_start->key.second});
            }
        }
        {
            int nxt = val_iter->second;
            auto nxt_start = node_roots[nxt];
            if (nxt_start) {
                q.push({l + nxt_start->key.first, nxt_start, nxt_start->key.second});
            }
        }
    }
    return res;
}
