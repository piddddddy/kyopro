#include <vector>

template<int M> struct modint {
    using mint = modint<M>;
private :
    int val;
public :
    modint() : val(0) { }
    template<typename T> modint(T val_) : val(val_ % M) { if (val < 0) val += M; }
    template<typename T> mint raw(T val_) const noexcept {
        mint ret; ret.val = val_;
        return ret;
    }
    template<typename T> mint pow(T n) const noexcept {
        static_assert(std::is_integral_v<T>);
        if (n == 0) return raw(1);
        return (*this * *this).pow(n / 2) * (n & 1 ? *this : raw(1));
    }
    mint inv() const noexcept { return pow(M - 2); }
    mint operator+(const mint& rhs) const noexcept {
        return raw(val + rhs.val < M ? val + rhs.val : val + rhs.val - M);
    }
    mint operator-(const mint& rhs) const noexcept {
        return raw(val < rhs.val ? val - rhs.val + M : val - rhs.val);
    }
    mint operator*(const mint& rhs) const noexcept {
        long long tmp = val; (tmp *= rhs.val) %= M;
        return raw(tmp < 0 ? tmp + M : tmp);
    }
    mint operator/(const mint& rhs) const noexcept { return *this * rhs.inv(); }
    mint& operator+=(const mint& rhs) noexcept {
        val = (val + rhs.val < M ? val + rhs.val : val + rhs.val - M);
        return *this;
    }
    mint& operator-=(const mint& rhs) noexcept {
        val = (val < rhs.val ? val - rhs.val + M : val - rhs.val);
        return *this;
    }
    mint& operator*=(const mint& rhs) noexcept {
        (val *= rhs.val) %= M;
        return *this;
    }
    mint& operator/=(const mint& rhs) noexcept { return *this *= rhs.inv(); }
    mint& operator++() noexcept { return *this += raw(1); }
    mint& operator--() noexcept { return *this -= raw(1); }
    mint operator++(int) noexcept { ++(*this) - raw(1); }
    mint operator--(int) noexcept { --(*this) + raw(1); }
    bool operator==(const mint& rhs) const noexcept { return val == rhs.val; }
    bool operator!=(const mint& rhs) const noexcept { return val != rhs.val; }
    int get() const noexcept { return val; }
};

template<int M> struct modfact {
    using mint = modint<M>;
private :
    int size = 1;
    std::vector<mint> fact = {1}, fact_inv = {1};
public :
    void extend(int SIZE) noexcept {
        if (SIZE <= size) return;
        fact.resize(SIZE); fact_inv.resize(SIZE);
        for (int i = size; i < SIZE; i++) fact[i] = fact[i - 1] * i;
        fact_inv[SIZE - 1] = fact[SIZE - 1].inv();
        for (int i = SIZE - 2; i >= size; i--) fact_inv[i] = fact_inv[i + 1] * (i + 1);
        size = SIZE;
    }
    mint get(int i) noexcept {
        extend(i + 1);
        return fact[i];
    }
    mint get_inv(int i) noexcept {
        extend(i + 1);
        return fact_inv[i];
    }
    mint permutation(int n, int k) noexcept {
        if (n < 0 || k < 0 || n < k) return mint();
        return get(n) * get_inv(n - k);
    }
    mint combination(int n, int k) noexcept {
        if (n < 0 || k < 0 || n < k) return mint();
        return permutation(n, k) * get_inv(k);
    }
};
