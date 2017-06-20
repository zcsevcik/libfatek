/*
 * zcsevcik/libfatek/address.cpp
 *
 * Author(s):      Radek Sevcik <zcsevcik@gmail.com>
 * Date:           2017/05/28
 *
 * This file is part of zcsevcik/libfatek.
 */

#include "address.hpp"
#include "detail/address-loader.hpp"
#include "detail/symbol.hpp"
#include "detail/symbol-dispatch.hpp"
#include <cstdarg>

namespace zcsevcik {
namespace libfatek {
/* ======================================================================= */
address::address() noexcept
  : value{}
{
}

address address::parse(const char* s, bool& success) noexcept
{
    using namespace detail;
    address a = address{};

    auto sym = symbol::from_string(s);
    if (!sym) {
        return success=false, a;
    }

    return success=dispatch(sym).invoke<bool, loader, char*>
                                       (loader{sym, s}, &a.value[0]),
           a;
}

const char* address::dump() const noexcept
{
    return &value[0];
}

/* ======================================================================= */
inline bool is_address_bytes_occupied(const char* s, int numchar) noexcept
{
    return *s && s[numchar-1] && !s[numchar];
}

bool address::is_discrete_address() const noexcept
{
    return is_address_bytes_occupied(value, 5);
}

bool address::is_register_16_address() const noexcept
{
    return is_address_bytes_occupied(value, 6);
}

bool address::is_register_32_address() const noexcept
{
    return is_address_bytes_occupied(value, 7);
}

/* ======================================================================= */
static bool is_typeof(const char* s, int n, ...) noexcept
{
    using detail::symbol;

    auto symbol = symbol::from_string(s);
    if (!symbol) return false;
    bool result = false;

    std::va_list args;
    va_start(args, n);
    while (n--) {
        auto symbol_arg = static_cast<symbol::value_type>( va_arg(args, int) );
        result |= (symbol == symbol_arg);
    }
    va_end(args);
    return result;
}

bool address::is_input_discrete() const noexcept
{
    using detail::symbol;
    return is_typeof(dump(), 3, symbol::X, symbol::WX, symbol::DWX);
}

bool address::is_output_relay() const noexcept
{
    using detail::symbol;
    return is_typeof(dump(), 3, symbol::Y, symbol::WY, symbol::DWY);
}

bool address::is_internal_relay() const noexcept
{
    using detail::symbol;
    return is_typeof(dump(), 3, symbol::M, symbol::WM, symbol::DWM);
}

bool address::is_step_relay() const noexcept
{
    using detail::symbol;
    return is_typeof(dump(), 3, symbol::S, symbol::WS, symbol::DWS);
}

bool address::is_timer_discrete() const noexcept
{
    using detail::symbol;
    return is_typeof(dump(), 3, symbol::T, symbol::WT, symbol::DWT);
}

bool address::is_counter_discrete() const noexcept
{
    using detail::symbol;
    return is_typeof(dump(), 3, symbol::C, symbol::WC, symbol::DWC);
}

bool address::is_timer_register() const noexcept
{
    using detail::symbol;
    return is_typeof(dump(), 2, symbol::RT, symbol::DRT);
}

bool address::is_counter_register() const noexcept
{
    using detail::symbol;
    return is_typeof(dump(), 2, symbol::RC, symbol::DRC);
}

bool address::is_data_register_hr() const noexcept
{
    using detail::symbol;
    return is_typeof(dump(), 2, symbol::R, symbol::DR);
}

bool address::is_data_register_dr() const noexcept
{
    using detail::symbol;
    return is_typeof(dump(), 2, symbol::D, symbol::DD);
}

bool address::is_file_register() const noexcept
{
    using detail::symbol;
    return is_typeof(dump(), 2, symbol::F, symbol::DF);
}

/* ======================================================================= */
} /* namespace libfatek */
} /* namespace zcsevcik */
