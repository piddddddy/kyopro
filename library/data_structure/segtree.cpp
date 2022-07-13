#include <vector>

template<typename T, class F> struct segtree {
private :
    const int N;
    std::vector<T> v;
    const F f;
    const T e;
    T buffer;
    int last_referenced = 0;
    void update(int i) noexcept { v[i] = f(v[i << 1], v[i << 1 | 1]); }
    void update() noexcept {
        v[last_referenced] = buffer;
        while (last_referenced >>= 1) update(last_referenced);
    }
public :
    template<class Iterator> segtree(Iterator first, Iterator last, F f_, T e_)
    : N(last - first), v(N * 2), f(f_), e(e_) {
        for (int i = 0; i < N; i++) v[i + N] = *(first++);
        for (int i = N - 1; i; i--) update(i);
    }
    segtree(int N_, T x, F f_, T e_) : N(N_), v(N * 2, x), f(f_), e(e_) {
        for (int i = N - 1; i; i--) update(i);
    }
    T& operator[](int i) noexcept {
        update();
        return buffer = v[last_referenced = i + N];
    }
    T fold(int l, int r) noexcept {
        update();
        l += N; r += N;
        T ret_l = e, ret_r = e;
        while (l < r) {
            if (l & 1) ret_l = f(ret_l, v[l++]);
            if (r & 1) ret_r = f(v[--r], ret_r);
            l >>= 1; r >>= 1;
        }
        return f(ret_l, ret_r);
    }
};
