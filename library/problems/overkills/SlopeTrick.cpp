#include <limits>
#include <queue>
#include <utility>

template <typename T>
struct SlopeTrick {
  static constexpr T inf = std::numeric_limits<T>::max() / 2;

  T cost = 0, left_offset = 0, right_offset = 0;
  using Pair = std::pair<T, T>;
  std::priority_queue<Pair> left;
  std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> right;

  SlopeTrick() {
    left.emplace(-inf, 0);
    right.emplace(+inf, 0);
  }

  void rebalance() {
    while (true) {
      auto [xl, sl] = left.top();
      xl -= left_offset;
      auto [xr, sr] = right.top();
      xr += right_offset;
      if (xl <= xr) break;
      left.pop();
      right.pop();
      T take = std::min(sl, sr);
      cost += take * (xl - xr);
      sl -= take;
      sr -= take;
      left.emplace(xr + left_offset, take);
      right.emplace(xl - right_offset, take);
      if (sl) {
        left.emplace(xl + left_offset, sl);
      }
      if (sr) {
        right.emplace(xr - right_offset, sr);
      }
    }
  }

  // Adds f(x) = s * max(a - x, 0).
  void add_left(T a, T s) {
    left.emplace(a + left_offset, s);
    rebalance();
  }

  // Adds f(x) = s * max(x - a, 0).
  void add_right(T a, T s) {
    right.emplace(a - right_offset, s);
    rebalance();
  }

  // Adds f(x) = s * abs(x - a).
  void add_abs(T a, T s) {
    add_left(a, s);
    add_right(a, s);
  }

  void relax_left(T offset) {
    assert(offset >= 0);
    left_offset += offset;
  }

  void relax_right(T offset) {
    assert(offset >= 0);
    right_offset += offset;
  }

  void relax(T offset) {
    assert(offset >= 0);
    left_offset += offset;
    right_offset += offset;
  }
};