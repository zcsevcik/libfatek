/*
 * zcsevcik/libfatek/detail/address/parser.hpp
 *
 * Author(s):      Radek Sevcik <zcsevcik@gmail.com>
 * Date:           2017/06/20
 *
 * This file is part of zcsevcik/libfatek.
 */

#ifndef ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_PARSER_HPP_
#define ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_PARSER_HPP_

#include "address.hpp"
#include "detail/address/basic_parser.hpp"
#include "detail/address/alignment.hpp"
#include "detail/address/limits.hpp"
#include <cstdint>

namespace zcsevcik {
namespace libfatek {
namespace detail {

class parser final
{
    const char* input;

public:
    explicit parser(const char* s) noexcept
      : input(s)
    {
    }

public:
    address::symbol_t operator()(uint16_t& address) const
    {
        address::symbol_t symbol = basic_parser{input}(&address);

        if (symbol == address::invalid_symbol)
            return address::invalid_symbol;
        if (!limits{symbol, address}.in_range())
            return address::invalid_symbol;
        if (!alignment{symbol, address}())
            return address::invalid_symbol;

        return symbol;
    }

};

} /* namespace detail */
} /* namespace zcsevcik */
} /* namespace libfatek */

#endif /* ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_PARSER_HPP_ */
