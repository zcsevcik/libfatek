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
    bool contiguous() const noexcept
    { return true; }

    bool alignas_8() const noexcept
    { return addr % 8 == 0; }

public:
    explicit alignment(address::symbol_t sym_, uint16_t addr_)
      : dispatch_layout(sym_)
      , addr(addr_)
    {
    }

    bool operator()() const {
        return ( this->*dispatch_layout() )();
    }

private:
    struct layout final
    {
        constexpr static auto X()   noexcept { return &alignment::contiguous; }
        constexpr static auto WX()  noexcept { return &alignment::alignas_8; }
        constexpr static auto DWX() noexcept { return &alignment::alignas_8; }
        constexpr static auto Y()   noexcept { return &alignment::contiguous; }
        constexpr static auto WY()  noexcept { return &alignment::alignas_8; }
        constexpr static auto DWY() noexcept { return &alignment::alignas_8; }
        constexpr static auto M()   noexcept { return &alignment::contiguous; }
        constexpr static auto WM()  noexcept { return &alignment::alignas_8; }
        constexpr static auto DWM() noexcept { return &alignment::alignas_8; }
        constexpr static auto S()   noexcept { return &alignment::contiguous; }
        constexpr static auto WS()  noexcept { return &alignment::alignas_8; }
        constexpr static auto DWS() noexcept { return &alignment::alignas_8; }
        constexpr static auto T()   noexcept { return &alignment::contiguous; }
        constexpr static auto WT()  noexcept { return &alignment::alignas_8; }
        constexpr static auto DWT() noexcept { return &alignment::alignas_8; }
        constexpr static auto C()   noexcept { return &alignment::contiguous; }
        constexpr static auto WC()  noexcept { return &alignment::alignas_8; }
        constexpr static auto DWC() noexcept { return &alignment::alignas_8; }
        constexpr static auto RT()  noexcept { return &alignment::contiguous; }
        constexpr static auto DRT() noexcept { return &alignment::contiguous; }
        constexpr static auto RC()  noexcept { return &alignment::contiguous; }
        constexpr static auto DRC() noexcept { return &alignment::contiguous; }
        constexpr static auto R()   noexcept { return &alignment::contiguous; }
        constexpr static auto DR()  noexcept { return &alignment::contiguous; }
        constexpr static auto D()   noexcept { return &alignment::contiguous; }
        constexpr static auto DD()  noexcept { return &alignment::contiguous; }
        constexpr static auto F()   noexcept { return &alignment::contiguous; }
        constexpr static auto DF()  noexcept { return &alignment::contiguous; }
    };

private:
    using layout_t = bool(alignment::*)() const noexcept;
    dispatcher<layout_t, layout> dispatch_layout;
    uint16_t addr;
};

} /* namespace detail */
} /* namespace zcsevcik */
} /* namespace libfatek */

#endif /* ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_ALIGNMENT_HPP_ */
