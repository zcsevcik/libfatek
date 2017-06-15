/*
 * zcsevcik/libfatek/detail/address-loader.hpp
 *
 * Author(s):      Radek Sevcik <zcsevcik@gmail.com>
 * Date:           2017/06/01
 *
 * This file is part of zcsevcik/libfatek.
 */

#ifndef ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_LOADER_HPP_
#define ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_LOADER_HPP_

#include "detail/address-types.hpp"
#include "detail/address-memory.hpp"
#include "detail/symbol.hpp"
#include <cassert>
#include <cstring>
#include <cstdio>

namespace zcsevcik {
namespace libfatek {
namespace detail {
/* ======================================================================= */
class loader final
{
private:
    const char* s;
    const char* sym;

public:
    loader(symbol const& p_sym, const char* p_s) noexcept
      : s(p_s)
      , sym(nullptr)
    {
        this->sym = p_sym.to_string();
        assert(std::strncmp(this->sym, this->s, std::strlen(this->sym)) == 0);
    }

public:
    template<class Tag>
    bool operator()(Tag, char*) noexcept;

private:
    template<class Layout>
    bool parse(Layout, int numchar, int maxaddr, char* buf) noexcept
    {
        const int symlen = std::strlen(sym);
        int value = memory::u16_TryParse(&s[symlen]);
        if (value == -1)
            return false;
        if (value > maxaddr || value < 0)
            return false;
        if (!memory::is_aligned(Layout{}, value))
            return false;

        std::snprintf(buf, 8, "%s%0*d", sym, numchar-symlen, value);
        return true;
    }

};

/* ======================================================================= */
#define X(_, ...) \
    _(contiguous, counter_discrete, 5, 9999, ##__VA_ARGS__)      \
    _(contiguous, counter_register_16, 6, 9999, ##__VA_ARGS__)   \
    _(contiguous, counter_register_32, 7, 9998, ##__VA_ARGS__)   \
    _(contiguous, data_register_dr_16, 6, 65535, ##__VA_ARGS__)  \
    _(contiguous, data_register_dr_32, 7, 65534, ##__VA_ARGS__)  \
    _(contiguous, data_register_hr_16, 6, 65535, ##__VA_ARGS__)  \
    _(contiguous, data_register_hr_32, 7, 65534, ##__VA_ARGS__)  \
    _(contiguous, file_register_16, 6, 65535, ##__VA_ARGS__)     \
    _(contiguous, file_register_32, 7, 65534, ##__VA_ARGS__)     \
    _(contiguous, input_discrete, 5, 9999, ##__VA_ARGS__)        \
    _(contiguous, internal_relay, 5, 9999, ##__VA_ARGS__)        \
    _(contiguous, output_relay, 5, 9999, ##__VA_ARGS__)          \
    _(contiguous, step_relay, 5, 9999, ##__VA_ARGS__)            \
    _(contiguous, timer_discrete, 5, 9999, ##__VA_ARGS__)        \
    _(contiguous, timer_register_16, 6, 9999, ##__VA_ARGS__)     \
    _(contiguous, timer_register_32, 7, 9998, ##__VA_ARGS__)     \
    _(alignas_8, counter_discrete_16, 6, 9984, ##__VA_ARGS__)      \
    _(alignas_8, counter_discrete_32, 7, 9968, ##__VA_ARGS__)      \
    _(alignas_8, input_discrete_16, 6, 9984, ##__VA_ARGS__)        \
    _(alignas_8, input_discrete_32, 7, 9968, ##__VA_ARGS__)        \
    _(alignas_8, internal_relay_16, 6, 9984, ##__VA_ARGS__)        \
    _(alignas_8, internal_relay_32, 7, 9968, ##__VA_ARGS__)        \
    _(alignas_8, output_relay_16, 6, 9984, ##__VA_ARGS__)          \
    _(alignas_8, output_relay_32, 7, 9968, ##__VA_ARGS__)          \
    _(alignas_8, step_relay_16, 6, 9984, ##__VA_ARGS__)            \
    _(alignas_8, step_relay_32, 7, 9968, ##__VA_ARGS__)            \
    _(alignas_8, timer_discrete_16, 6, 9984, ##__VA_ARGS__)        \
    _(alignas_8, timer_discrete_32, 7, 9968, ##__VA_ARGS__)        \

#define call_op(layout, tag, numchar, maxaddr) \
template<> bool loader::operator()<tag>(tag, char* buf) noexcept { \
    return parse(memory::layout{}, numchar, maxaddr, buf); \
}

X(call_op)
#undef X
#undef call_op

} /* namespace detail */
} /* namespace zcsevcik */
} /* namespace libfatek */

#endif /* ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_LOADER_HPP_ */
