#include "../../contest/header.hpp"

/*
	MO's using Hilbert Curve to sort the queries.
    O(N * sqrt(Q) * max(insertion time, removal time)).
    Applicability:
    When Q is significantly less than N, it works much faster than
	the classical version.
    Usage:
    Same as the classical version, but use the query's hilbertorder 
	as comparator
*/

constexpr int logn = 20;
constexpr int maxn = 1 << logn;
ll hilbertorder(int x, int y)
{
	ll d = 0;
	for (int s = 1 << (logn - 1); s; s >>= 1)
	{
		bool rx = x & s, ry = y & s;
		d = d << 2 | rx * 3 ^ static_cast<int>(ry);
		if (!ry)
		{
			if (rx)
			{
				x = maxn - x;
				y = maxn - y;
			}
			swap(x, y);
		}
	}
	return d;
}
 
struct query {
	int l, r, id;
    ll ord() const
    {
        return hilbertorder(l, r);
    }
};

template<class F>
void mos(int n, vector<query> q, const F &add, const F &remove, const F &output)
{
	int bsize = 1 + n / sqrt(sz(q));
	sort(q.begin(), q.end(), [&](const query &lhs, const query &rhs) {
        return lhs.ord() < rhs.ord();
	});

	int l = 1, r = 0; // int l = 0, r = -1; (if indices starts at 0)
	for (int i = 0; i < sz(q); i++)
	{
		while (l > q[i].l)
			add(--l);
		while (r < q[i].r)
			add(++r);
		while (l < q[i].l)
			remove(l++);
		while (r > q[i].r)
			remove(r--);

		output(q[i].id);
	}
}
