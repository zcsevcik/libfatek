/*
 * zcsevcik/libfatek/address.cpp
 *
 * Author(s):      Radek Sevcik <zcsevcik@gmail.com>
 * Date:           2017/05/28
 *
 * This file is part of zcsevcik/libfatek.
 */

#include "address.hpp"
#include "detail/address/dumper.hpp"
#include "detail/address/parser.hpp"
#include <algorithm>
#include <initializer_list>

namespace zcsevcik {
namespace libfatek {
/* ======================================================================= */
address::address() noexcept
  : value{}
{
}

address address::parse(const char* s, bool& success) noexcept
{
    uint16_t addr = 0;
    symbol_t symbol = detail::parser{s}(addr);

    if (symbol == invalid_symbol)
        return success=false, address{};

    address out;
    detail::dumper{symbol, addr}(&out.value[0]);
    return success=true, out;
}

address::symbol_t address::symbol() const noexcept
{
    return detail::basic_parser{dump()}();
}

const char* address::dump() const noexcept
{
    return &value[0];
}

/* ======================================================================= */
inline bool
is_address_bytes_occupied(const char* s, int numchar) noexcept
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
static bool
includes_(address::symbol_t search_for,
          std::initializer_list<address::symbol_t> examine_list) noexcept
{
    return std::includes(begin(examine_list), end(examine_list),
                         &search_for, &search_for+1);
}

bool address::is_input_discrete() const noexcept {
    return includes_(symbol(), { X, WX, DWX });
}

bool address::is_output_relay() const noexcept {
    return includes_(symbol(), { Y, WY, DWY });
}

bool address::is_internal_relay() const noexcept {
    return includes_(symbol(), { M, WM, DWM });
}

bool address::is_step_relay() const noexcept {
    return includes_(symbol(), { S, WS, DWS });
}

bool address::is_timer_discrete() const noexcept {
    return includes_(symbol(), { T, WT, DWT });
}

bool address::is_counter_discrete() const noexcept {
    return includes_(symbol(), { C, WC, DWC });
}

bool address::is_timer_register() const noexcept {
    return includes_(symbol(), { RT, DRT });
}

bool address::is_counter_register() const noexcept {
    return includes_(symbol(), { RC, DRC });
}

bool address::is_data_register_hr() const noexcept {
    return includes_(symbol(), { R, DR });
}

bool address::is_data_register_dr() const noexcept {
    return includes_(symbol(), { D, DD });
}

bool address::is_file_register() const noexcept {
    return includes_(symbol(), { F, DF });
}

/* ======================================================================= */
} /* namespace libfatek */
} /* namespace zcsevcik */
