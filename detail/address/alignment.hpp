/*
 * zcsevcik/libfatek/detail/address/alignment.hpp
 *
 * Author(s):      Radek Sevcik <zcsevcik@gmail.com>
 * Date:           2017/06/02
 *
 * This file is part of zcsevcik/libfatek.
 */

#ifndef ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_ALIGNMENT_HPP_
#define ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_ALIGNMENT_HPP_

#include "address.hpp"
#include "detail/address/dispatcher.hpp"
#include <cstdint>

namespace zcsevcik {
namespace libfatek {
namespace detail {

class alignment final
{
    using layout_t = bool(alignment::*)() const noexcept;

    dispatcher<layout_t> dispatch_layout;
    uint16_t addr;

public:
    explicit alignment(address::symbol_t sym_, uint16_t addr_)
      : dispatch_layout(sym_, layout{})
      , addr(addr_)
    {
    }

    bool operator()() const {
        return ( this->*dispatch_layout() )();
    }

private:
    bool contiguous() const noexcept
    { return true; }

    bool alignas_8() const noexcept
    { return addr % 8 == 0; }

    struct layout final
    {
        constexpr auto X()   const noexcept { return &alignment::contiguous; }
        constexpr auto WX()  const noexcept { return &alignment::alignas_8; }
        constexpr auto DWX() const noexcept { return &alignment::alignas_8; }
        constexpr auto Y()   const noexcept { return &alignment::contiguous; }
        constexpr auto WY()  const noexcept { return &alignment::alignas_8; }
        constexpr auto DWY() const noexcept { return &alignment::alignas_8; }
        constexpr auto M()   const noexcept { return &alignment::contiguous; }
        constexpr auto WM()  const noexcept { return &alignment::alignas_8; }
        constexpr auto DWM() const noexcept { return &alignment::alignas_8; }
        constexpr auto S()   const noexcept { return &alignment::contiguous; }
        constexpr auto WS()  const noexcept { return &alignment::alignas_8; }
        constexpr auto DWS() const noexcept { return &alignment::alignas_8; }
        constexpr auto T()   const noexcept { return &alignment::contiguous; }
        constexpr auto WT()  const noexcept { return &alignment::alignas_8; }
        constexpr auto DWT() const noexcept { return &alignment::alignas_8; }
        constexpr auto C()   const noexcept { return &alignment::contiguous; }
        constexpr auto WC()  const noexcept { return &alignment::alignas_8; }
        constexpr auto DWC() const noexcept { return &alignment::alignas_8; }
        constexpr auto RT()  const noexcept { return &alignment::contiguous; }
        constexpr auto DRT() const noexcept { return &alignment::contiguous; }
        constexpr auto RC()  const noexcept { return &alignment::contiguous; }
        constexpr auto DRC() const noexcept { return &alignment::contiguous; }
        constexpr auto R()   const noexcept { return &alignment::contiguous; }
        constexpr auto DR()  const noexcept { return &alignment::contiguous; }
        constexpr auto D()   const noexcept { return &alignment::contiguous; }
        constexpr auto DD()  const noexcept { return &alignment::contiguous; }
        constexpr auto F()   const noexcept { return &alignment::contiguous; }
        constexpr auto DF()  const noexcept { return &alignment::contiguous; }
    };
};

} /* namespace detail */
} /* namespace zcsevcik */
} /* namespace libfatek */

#endif /* ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_ALIGNMENT_HPP_ */
