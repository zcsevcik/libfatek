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
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace zcsevcik {
namespace libfatek {
namespace detail {

class dumper final
{
    dispatcher<char const*> dispatch_symbol;
    dispatcher<int> dispatch_maxlength;
    uint16_t addr;

public:
    explicit dumper(address::symbol_t sym_, uint16_t addr_)
      : dispatch_symbol(sym_, symbol{})
      , dispatch_maxlength(sym_, max_length{})
      , addr(addr_)
    {
    }

    std::size_t operator()(char* out) const
    {
        const char* strSym = dispatch_symbol();
        const int lenSym = static_cast<int>(std::strlen(strSym));
        const int addrlen = dispatch_maxlength() - lenSym;
        return std::snprintf(out, 8, "%s%0*hu", strSym, addrlen, addr);
    }

public:
    struct symbol final
    {
        constexpr auto X() const noexcept { return "X"; }
        constexpr auto WX() const noexcept { return "WX"; }
        constexpr auto DWX() const noexcept { return "DWX"; }
        constexpr auto Y() const noexcept { return "Y"; }
        constexpr auto WY() const noexcept { return "WY"; }
        constexpr auto DWY() const noexcept { return "DWY"; }
        constexpr auto M() const noexcept { return "M"; }
        constexpr auto WM() const noexcept { return "WM"; }
        constexpr auto DWM() const noexcept { return "DWM"; }
        constexpr auto S() const noexcept { return "S"; }
        constexpr auto WS() const noexcept { return "WS"; }
        constexpr auto DWS() const noexcept { return "DWS"; }
        constexpr auto T() const noexcept { return "T"; }
        constexpr auto WT() const noexcept { return "WT"; }
        constexpr auto DWT() const noexcept { return "DWT"; }
        constexpr auto C() const noexcept { return "C"; }
        constexpr auto WC() const noexcept { return "WC"; }
        constexpr auto DWC() const noexcept { return "DWC"; }
        constexpr auto RT() const noexcept { return "RT"; }
        constexpr auto DRT() const noexcept { return "DRT"; }
        constexpr auto RC() const noexcept { return "RC"; }
        constexpr auto DRC() const noexcept { return "DRC"; }
        constexpr auto R() const noexcept { return "R"; }
        constexpr auto DR() const noexcept { return "DR"; }
        constexpr auto D() const noexcept { return "D"; }
        constexpr auto DD() const noexcept { return "DD"; }
        constexpr auto F() const noexcept { return "F"; }
        constexpr auto DF() const noexcept { return "DF"; }
    };

public:
    struct max_length final
    {
        constexpr static int DISCRETE_SIZE = 5;
        constexpr static int REGISTER_SIZE = 6;
        constexpr static int DOUBLE_REGISTER_SIZE = 7;

        constexpr auto X() const noexcept { return DISCRETE_SIZE; }
        constexpr auto WX() const noexcept { return REGISTER_SIZE; }
        constexpr auto DWX() const noexcept { return DOUBLE_REGISTER_SIZE; }
        constexpr auto Y() const noexcept { return DISCRETE_SIZE; }
        constexpr auto WY() const noexcept { return REGISTER_SIZE; }
        constexpr auto DWY() const noexcept { return DOUBLE_REGISTER_SIZE; }
        constexpr auto M() const noexcept { return DISCRETE_SIZE; }
        constexpr auto WM() const noexcept { return REGISTER_SIZE; }
        constexpr auto DWM() const noexcept { return DOUBLE_REGISTER_SIZE; }
        constexpr auto S() const noexcept { return DISCRETE_SIZE; }
        constexpr auto WS() const noexcept { return REGISTER_SIZE; }
        constexpr auto DWS() const noexcept { return DOUBLE_REGISTER_SIZE; }
        constexpr auto T() const noexcept { return DISCRETE_SIZE; }
        constexpr auto WT() const noexcept { return REGISTER_SIZE; }
        constexpr auto DWT() const noexcept { return DOUBLE_REGISTER_SIZE; }
        constexpr auto C() const noexcept { return DISCRETE_SIZE; }
        constexpr auto WC() const noexcept { return REGISTER_SIZE; }
        constexpr auto DWC() const noexcept { return DOUBLE_REGISTER_SIZE; }
        constexpr auto RT() const noexcept { return REGISTER_SIZE; }
        constexpr auto DRT() const noexcept { return DOUBLE_REGISTER_SIZE; }
        constexpr auto RC() const noexcept { return REGISTER_SIZE; }
        constexpr auto DRC() const noexcept { return DOUBLE_REGISTER_SIZE; }
        constexpr auto R() const noexcept { return REGISTER_SIZE; }
        constexpr auto DR() const noexcept { return DOUBLE_REGISTER_SIZE; }
        constexpr auto D() const noexcept { return REGISTER_SIZE; }
        constexpr auto DD() const noexcept { return DOUBLE_REGISTER_SIZE; }
        constexpr auto F() const noexcept { return REGISTER_SIZE; }
        constexpr auto DF() const noexcept { return DOUBLE_REGISTER_SIZE; }
    };
};

} /* namespace detail */
} /* namespace zcsevcik */
} /* namespace libfatek */

#endif /* ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_DUMPER_HPP_ */
