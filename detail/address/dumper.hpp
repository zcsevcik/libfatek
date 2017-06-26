/*
 * zcsevcik/libfatek/detail/address/dumper.hpp
 *
 * Author(s):      Radek Sevcik <zcsevcik@gmail.com>
 * Date:           2017/06/20
 *
 * This file is part of zcsevcik/libfatek.
 */

#ifndef ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_DUMPER_HPP_
#define ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_DUMPER_HPP_

#include "address.hpp"
#include "detail/address/dispatcher.hpp"
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace zcsevcik {
namespace libfatek {
namespace detail {

class dumper final
{
public:
    explicit dumper(address::symbol_t sym_, uint16_t addr_)
      : dispatch_symbol(sym_)
      , dispatch_maxlength(sym_)
      , addr(addr_)
    {
    }

    int operator()(char* out, int size) const
    {
        const char* strSym = dispatch_symbol();
        const int lenSym = static_cast<int>(std::strlen(strSym));
        const int addrlen = dispatch_maxlength() - lenSym;
        int nchars = std::snprintf(out, size, "%s%0*hu", strSym, addrlen, addr);
        if (nchars > 0 and not(nchars >= size))
            std::fill_n(&out[nchars], size - nchars, '\0');
        return nchars;
    }

public:
    struct symbol final
    {
        constexpr static auto X() noexcept { return "X"; }
        constexpr static auto WX() noexcept { return "WX"; }
        constexpr static auto DWX() noexcept { return "DWX"; }
        constexpr static auto Y() noexcept { return "Y"; }
        constexpr static auto WY() noexcept { return "WY"; }
        constexpr static auto DWY() noexcept { return "DWY"; }
        constexpr static auto M() noexcept { return "M"; }
        constexpr static auto WM() noexcept { return "WM"; }
        constexpr static auto DWM() noexcept { return "DWM"; }
        constexpr static auto S() noexcept { return "S"; }
        constexpr static auto WS() noexcept { return "WS"; }
        constexpr static auto DWS() noexcept { return "DWS"; }
        constexpr static auto T() noexcept { return "T"; }
        constexpr static auto WT() noexcept { return "WT"; }
        constexpr static auto DWT() noexcept { return "DWT"; }
        constexpr static auto C() noexcept { return "C"; }
        constexpr static auto WC() noexcept { return "WC"; }
        constexpr static auto DWC() noexcept { return "DWC"; }
        constexpr static auto RT() noexcept { return "RT"; }
        constexpr static auto DRT() noexcept { return "DRT"; }
        constexpr static auto RC() noexcept { return "RC"; }
        constexpr static auto DRC() noexcept { return "DRC"; }
        constexpr static auto R() noexcept { return "R"; }
        constexpr static auto DR() noexcept { return "DR"; }
        constexpr static auto D() noexcept { return "D"; }
        constexpr static auto DD() noexcept { return "DD"; }
        constexpr static auto F() noexcept { return "F"; }
        constexpr static auto DF() noexcept { return "DF"; }
    };

public:
    struct max_length final
    {
        constexpr static int DISCRETE_SIZE = 5;
        constexpr static int REGISTER_SIZE = 6;
        constexpr static int DOUBLE_REGISTER_SIZE = 7;

        constexpr static auto X() noexcept { return DISCRETE_SIZE; }
        constexpr static auto WX() noexcept { return REGISTER_SIZE; }
        constexpr static auto DWX() noexcept { return DOUBLE_REGISTER_SIZE; }
        constexpr static auto Y() noexcept { return DISCRETE_SIZE; }
        constexpr static auto WY() noexcept { return REGISTER_SIZE; }
        constexpr static auto DWY() noexcept { return DOUBLE_REGISTER_SIZE; }
        constexpr static auto M() noexcept { return DISCRETE_SIZE; }
        constexpr static auto WM() noexcept { return REGISTER_SIZE; }
        constexpr static auto DWM() noexcept { return DOUBLE_REGISTER_SIZE; }
        constexpr static auto S() noexcept { return DISCRETE_SIZE; }
        constexpr static auto WS() noexcept { return REGISTER_SIZE; }
        constexpr static auto DWS() noexcept { return DOUBLE_REGISTER_SIZE; }
        constexpr static auto T() noexcept { return DISCRETE_SIZE; }
        constexpr static auto WT() noexcept { return REGISTER_SIZE; }
        constexpr static auto DWT() noexcept { return DOUBLE_REGISTER_SIZE; }
        constexpr static auto C() noexcept { return DISCRETE_SIZE; }
        constexpr static auto WC() noexcept { return REGISTER_SIZE; }
        constexpr static auto DWC() noexcept { return DOUBLE_REGISTER_SIZE; }
        constexpr static auto RT() noexcept { return REGISTER_SIZE; }
        constexpr static auto DRT() noexcept { return DOUBLE_REGISTER_SIZE; }
        constexpr static auto RC() noexcept { return REGISTER_SIZE; }
        constexpr static auto DRC() noexcept { return DOUBLE_REGISTER_SIZE; }
        constexpr static auto R() noexcept { return REGISTER_SIZE; }
        constexpr static auto DR() noexcept { return DOUBLE_REGISTER_SIZE; }
        constexpr static auto D() noexcept { return REGISTER_SIZE; }
        constexpr static auto DD() noexcept { return DOUBLE_REGISTER_SIZE; }
        constexpr static auto F() noexcept { return REGISTER_SIZE; }
        constexpr static auto DF() noexcept { return DOUBLE_REGISTER_SIZE; }
    };

private:
    dispatcher<char const*, symbol> dispatch_symbol;
    dispatcher<int, max_length> dispatch_maxlength;
    uint16_t addr;
};

} /* namespace detail */
} /* namespace zcsevcik */
} /* namespace libfatek */

#endif /* ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_DUMPER_HPP_ */
