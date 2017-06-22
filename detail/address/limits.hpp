/*
 * zcsevcik/libfatek/detail/address/limits.hpp
 *
 * Author(s):      Radek Sevcik <zcsevcik@gmail.com>
 * Date:           2017/06/20
 *
 * This file is part of zcsevcik/libfatek.
 */

#ifndef ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_LIMITS_HPP_
#define ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_LIMITS_HPP_

#include "address.hpp"
#include "detail/address/dispatcher.hpp"

namespace zcsevcik {
namespace libfatek {
namespace detail {

class limits final
{
public:
    explicit limits(address::symbol_t sym_, uint16_t addr_)
      : dispatch_highest_address(sym_)
      , addr(addr_)
    {
    }

    bool in_range() const
    {
        return addr <= max();
    }

    uint16_t max() const {
        return dispatch_highest_address();
    }

private:
    struct highest_address final
    {
        constexpr static uint16_t X()   noexcept { return 9999; }
        constexpr static uint16_t WX()  noexcept { return 9984; }
        constexpr static uint16_t DWX() noexcept { return 9968; }
        constexpr static uint16_t Y()   noexcept { return 9999; }
        constexpr static uint16_t WY()  noexcept { return 9984; }
        constexpr static uint16_t DWY() noexcept { return 9968; }
        constexpr static uint16_t M()   noexcept { return 9999; }
        constexpr static uint16_t WM()  noexcept { return 9984; }
        constexpr static uint16_t DWM() noexcept { return 9968; }
        constexpr static uint16_t S()   noexcept { return 9999; }
        constexpr static uint16_t WS()  noexcept { return 9984; }
        constexpr static uint16_t DWS() noexcept { return 9968; }
        constexpr static uint16_t T()   noexcept { return 9999; }
        constexpr static uint16_t WT()  noexcept { return 9984; }
        constexpr static uint16_t DWT() noexcept { return 9968; }
        constexpr static uint16_t C()   noexcept { return 9999; }
        constexpr static uint16_t WC()  noexcept { return 9984; }
        constexpr static uint16_t DWC() noexcept { return 9968; }
        constexpr static uint16_t RT()  noexcept { return 9999; }
        constexpr static uint16_t DRT() noexcept { return 9998; }
        constexpr static uint16_t RC()  noexcept { return 9999; }
        constexpr static uint16_t DRC() noexcept { return 9998; }
        constexpr static uint16_t R()   noexcept { return 65535; }
        constexpr static uint16_t DR()  noexcept { return 65534; }
        constexpr static uint16_t D()   noexcept { return 65535; }
        constexpr static uint16_t DD()  noexcept { return 65534; }
        constexpr static uint16_t F()   noexcept { return 65535; }
        constexpr static uint16_t DF()  noexcept { return 65534; }
    };

private:
    dispatcher<uint16_t, highest_address> dispatch_highest_address;
    uint16_t addr;
};

} /* namespace detail */
} /* namespace zcsevcik */
} /* namespace libfatek */

#endif /* ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_LIMITS_HPP_ */
