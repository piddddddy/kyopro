#include <cstdio>
#include <bitset>
#ifdef _WIN32
#define getchar_unlocked _getchar_nolock
#define putchar_unlocked _putchar_nolock
#endif

namespace fast_IO {
    struct in {
    private :
        template<typename T> T read_integer() const noexcept {
            static_assert(std::is_same_v<T, int> || std::is_same_v<T, long long>);
            T n = 0;
            bool negative = false;
            char c = operator char();
            if (c == '-') negative = true, c = getchar_unlocked();
            while ('0' <= c && c <= '9') n = n * 10 + (c - '0'), c = getchar_unlocked();
            return negative ? -n : n;
        }
        template<typename T> T read_double() const noexcept {
            static_assert(std::is_same_v<T, double> || std::is_same_v<T, long double>);
            long long n = 0, div = 1;
            char c = operator char();
            if (c == '-') div = -1, c = getchar_unlocked();
            while ('0' <= c && c <= '9') n = n * 10 + (c - '0'), c = getchar_unlocked();
            if (c == '.') {
                c = getchar_unlocked();
                while ('0' <= c && c <= '9') n = n * 10 + (c - '0'), c = getchar_unlocked(), div *= 10;
            }
            return n / (double)div;
        }
    public :
        operator char() const noexcept {
            char c = getchar_unlocked();
            while (c == ' ' || c == '\n' || c == '\r') c = getchar_unlocked();
            return c;
        }
        template<typename T> operator T() const noexcept {
            if constexpr (std::is_integral_v<T>) return read_integer<T>();
            else return read_double<T>();
        }
    };
    template<class Iterator> void fill(Iterator first, Iterator last) noexcept {
        while (first != last) *(first++) = in();
    }
    void sin(std::string& s) noexcept {
        char c = in();
        while (c != ' ' && c != '\n' && c != '\r') s += c, c = getchar_unlocked();
    }
    void getline(std::string& s) noexcept {
        char c = in();
        while (c != '\n' && c != '\r') s += c, c = getchar_unlocked();
    }

    template<typename T> void put_raw(const T& t) noexcept {
        if constexpr (std::is_same_v<T, char>) putchar_unlocked(t);
        if constexpr (std::is_same_v<T, int>) printf("%d", t);
        if constexpr (std::is_same_v<T, unsigned>) printf("%u", t);
        if constexpr (std::is_same_v<T, unsigned long>) printf("%lu", t);
        if constexpr (std::is_same_v<T, long long>) printf("%lld", t);
        if constexpr (std::is_same_v<T, unsigned long long>) printf("%llu", t);
        if constexpr (std::is_same_v<T, double>) printf("%.20lf", t);
        if constexpr (std::is_same_v<T, long double>) printf("%.20Lf", t);
        if constexpr (std::is_same_v<T, const char*>) printf(t);
        if constexpr (std::is_same_v<T, std::string>) for (const auto& c : t) putchar_unlocked(c);
    }
    template<std::size_t N> void put_raw(const char (&s)[N]) noexcept {
        for (std::size_t i = 0; i < N; i++) putchar_unlocked(s[i]);
    }
    template<std::size_t N> void put_raw(const std::bitset<N>& bs) noexcept {
        for (std::size_t i = 0; i < N; i++) putchar_unlocked('0' + bs[N - 1 - i]);
    }

    bool line_head = true;
    void put() noexcept { }
    template<typename T, typename...Args> void put(T&& t, Args&&...args) noexcept {
        if (!line_head) putchar_unlocked(' ');
        else line_head = false;
        put_raw(t);
        put(std::forward<Args>(args)...);
    }
    template<typename...Args> void out(Args&&...args) noexcept {
        put(args...);
        putchar_unlocked('\n');
        line_head = true;
    }
    template<class Iterator> void dump(Iterator first, Iterator last) noexcept {
        while (first != last) put(*(first++));
        out();
    }
}

#ifdef _WIN32
#undef getchar_unlocked
#undef putchar_unlocked
#endif

using fast_IO::in;
using fast_IO::fill;
using fast_IO::sin;
using fast_IO::getline;
using fast_IO::put_raw;
using fast_IO::put;
using fast_IO::out;
using fast_IO::dump;
