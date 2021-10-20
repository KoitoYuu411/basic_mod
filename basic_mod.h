template< auto mod = (long long)1000000007 >
class basic_mod {
    using LL = decltype(mod);
    LL v;
public:
    basic_mod()=default;
    constexpr basic_mod(LL x) : v((x%=mod)<0?x+=mod:x) {} 
    template< class Int, class = enable_if_t<is_integral_v<Int> && !is_same_v<Int, int>, void> >
    explicit constexpr operator Int() const { return static_cast<Int>(v); }
    constexpr operator int() const { return static_cast<int>(v); }
    constexpr basic_mod& operator+=(basic_mod rhs) { v -= mod - rhs.v; if (v < 0) v += mod; return *this; }
    constexpr basic_mod& operator-=(basic_mod rhs) { v -= rhs.v; if (v < 0) v += mod; return *this;  }
    constexpr basic_mod& operator*=(basic_mod rhs) { v = (v * rhs.v) % mod; return *this; }
    constexpr basic_mod& operator/=(basic_mod rhs) { *this *= rhs.inv(); return *this; }
    friend constexpr basic_mod operator+(basic_mod lhs, basic_mod rhs) { return lhs += rhs; }
    friend constexpr basic_mod operator-(basic_mod lhs, basic_mod rhs) { return lhs -= rhs; }
    friend constexpr basic_mod operator*(basic_mod lhs, basic_mod rhs) { return lhs *= rhs; }
    friend constexpr basic_mod operator/(basic_mod lhs, basic_mod rhs) { return lhs /= rhs; }
    
    template< class Int > enable_if_t<is_integral_v<Int>, basic_mod>
    friend constexpr operator+(Int lhs, basic_mod rhs) { return static_cast<basic_mod>(lhs) += rhs; }
    template< class Int > enable_if_t<is_integral_v<Int>, basic_mod>
    friend constexpr operator-(Int lhs, basic_mod rhs) { return static_cast<basic_mod>(lhs) -= rhs; }
    template< class Int > enable_if_t<is_integral_v<Int>, basic_mod>
    friend constexpr operator*(Int lhs, basic_mod rhs) { return static_cast<basic_mod>(lhs) *= rhs; }
    template< class Int > enable_if_t<is_integral_v<Int>, basic_mod>
    friend constexpr operator/(Int lhs, basic_mod rhs) { return static_cast<basic_mod>(lhs) /= rhs; }
    
    template< class Int > enable_if_t<is_integral_v<Int>, basic_mod>
    friend constexpr operator+(basic_mod lhs, Int rhs) { return lhs += rhs; }
    template< class Int > enable_if_t<is_integral_v<Int>, basic_mod>
    friend constexpr operator-(basic_mod lhs, Int rhs) { return lhs -= rhs; }
    template< class Int > enable_if_t<is_integral_v<Int>, basic_mod>
    friend constexpr operator*(basic_mod lhs, Int rhs) { return lhs *= rhs; }
    template< class Int > enable_if_t<is_integral_v<Int>, basic_mod>
    friend constexpr operator/(basic_mod lhs, Int rhs) { return lhs /= rhs; }
    
    friend constexpr basic_mod operator+(basic_mod rhs) { return rhs; }
    friend constexpr basic_mod operator-(basic_mod rhs) { return 0 - rhs; }
    
    friend constexpr basic_mod inv(basic_mod x) { return x.pow(mod - 2); }
    template< class Int > enable_if_t<is_integral_v<Int>, basic_mod>
    friend constexpr pow(basic_mod lhs, Int rhs) { return lhs.pow(rhs); }
    
    constexpr basic_mod inv() const { return pow(mod - 2); }
    template< class Int > enable_if_t<is_integral_v<Int>, basic_mod>
    constexpr pow(Int rhs) const {
        basic_mod base = *this, ret = 1;
        while (rhs != 0) {
            if (rhs & 1) 
                ret *= base;
            base *= base;
            rhs >>= 1;
        }
        return ret;
    }

    template< class L, class R > enable_if_t<is_integral_v<L> && is_integral_v<R>, basic_mod>
    static constexpr pow(L lhs, R rhs) { return static_cast<basic_mod>(lhs).pow(rhs); }
    template< class Int > enable_if_t<is_integral_v<Int>, basic_mod>
    static fac(Int x) {
        static unordered_map<Int, basic_mod> fac_ { { 0, 1 } };
        if (auto it = fac_.find(x); it != end(fac_))
            return it -> second;
        auto ret = x * fac(x - 1);
        fac_.try_emplace(x, ret);
        return ret;
    }
    template< class Int > enable_if_t<is_integral_v<Int>, basic_mod>
    static comb(Int x, Int y) {
        if (x < y) swap(x, y);
        basic_mod ret = 1;
        ret *= fac(x);
        x -= y;
        ret /= fac(x) * fac(y);
        return ret;
    }
};
using mod = basic_mod<>;
inline constexpr mod operator""_mod (unsigned long long int x) { return mod (x); }
