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
    dispatcher<uint16_t> dispatch_highest_address;
    uint16_t addr;

public:
    explicit limits(address::symbol_t sym_, uint16_t addr_)
      : dispatch_highest_address(sym_, highest_address{})
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
        constexpr uint16_t X()   const noexcept { return 9999; }
        constexpr uint16_t WX()  const noexcept { return 9984; }
        constexpr uint16_t DWX() const noexcept { return 9968; }
        constexpr uint16_t Y()   const noexcept { return 9999; }
        constexpr uint16_t WY()  const noexcept { return 9984; }
        constexpr uint16_t DWY() const noexcept { return 9968; }
        constexpr uint16_t M()   const noexcept { return 9999; }
        constexpr uint16_t WM()  const noexcept { return 9984; }
        constexpr uint16_t DWM() const noexcept { return 9968; }
        constexpr uint16_t S()   const noexcept { return 9999; }
        constexpr uint16_t WS()  const noexcept { return 9984; }
        constexpr uint16_t DWS() const noexcept { return 9968; }
        constexpr uint16_t T()   const noexcept { return 9999; }
        constexpr uint16_t WT()  const noexcept { return 9984; }
        constexpr uint16_t DWT() const noexcept { return 9968; }
        constexpr uint16_t C()   const noexcept { return 9999; }
        constexpr uint16_t WC()  const noexcept { return 9984; }
        constexpr uint16_t DWC() const noexcept { return 9968; }
        constexpr uint16_t RT()  const noexcept { return 9999; }
        constexpr uint16_t DRT() const noexcept { return 9998; }
        constexpr uint16_t RC()  const noexcept { return 9999; }
        constexpr uint16_t DRC() const noexcept { return 9998; }
        constexpr uint16_t R()   const noexcept { return 65535; }
        constexpr uint16_t DR()  const noexcept { return 65534; }
        constexpr uint16_t D()   const noexcept { return 65535; }
        constexpr uint16_t DD()  const noexcept { return 65534; }
        constexpr uint16_t F()   const noexcept { return 65535; }
        constexpr uint16_t DF()  const noexcept { return 65534; }
    };
};

} /* namespace detail */
} /* namespace zcsevcik */
} /* namespace libfatek */

#endif /* ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_LIMITS_HPP_ */
