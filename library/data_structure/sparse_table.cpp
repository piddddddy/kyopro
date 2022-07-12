#include <functional>

template<typename T> struct sparse_table {
    using F = std::function<T(T, T)>;
private :
    const int N;
    std::vector<std::vector<T>> table;
    std::vector<int> log2;
    const F f;
public :
    template<class Iterator> sparse_table(Iterator first, Iterator last, F f_)
    : N(last - first), table(N), log2(N + 1), f(f_) {
        int m = 0;
        for (int i = N - 1; i >= 0; i--) {
            log2[N - i] = ((1 << (m + 1)) <= N - i ? ++m : m);
            table[i].resize(log2[N - i] + 1, *(--last));
            for (int j = 1; j <= log2[N - i]; j++) {
                table[i][j] = f(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    T fold(int l, int r) const noexcept {
        return f(table[l][log2[r - l]], table[r - (1 << log2[r - l])][log2[r - l]]);
    }
};
