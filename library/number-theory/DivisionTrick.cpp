// by tfg50 - floor(n/i) business in sqrt(N)
for(int l = 1, r; l <= n; l = r + 1) {
	r = n / (n / l);
	// n / i has the same value for l <= i <= r
}
