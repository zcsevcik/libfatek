/*
 * zcsevcik/libfatek/detail/address/basic_parser.hpp
 *
 * Author(s):      Radek Sevcik <zcsevcik@gmail.com>
 * Date:           2017/06/20
 *
 * This file is part of zcsevcik/libfatek.
 */

#ifndef ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_BASIC_PARSER_HPP_
#define ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_BASIC_PARSER_HPP_

#include "address.hpp"
#include <algorithm>
#include <cerrno>
#include <cstdlib>
#include <locale>

namespace zcsevcik {
namespace libfatek {
namespace detail {
/* ======================================================================= */
class basic_parser final
{
    const char* input;

public:
    explicit basic_parser(const char* s) noexcept
      : input(s)
    {
    }

public:
    address::symbol_t operator()(uint16_t* address = nullptr) const noexcept
    {
        address::symbol_t sym = symbol(input);
        if (sym == address::invalid_symbol)
            return address::invalid_symbol;

        if (address != nullptr)
        {
            const char* strNum = &input[find_first_not_upper_ascii(input)];
            int iAddress = u16(strNum);

            if (iAddress == -1)
                return address::invalid_symbol;
            *address = static_cast<uint16_t>(iAddress);
        }

        return sym;
    }

private:
    static address::symbol_t symbol(const char*) noexcept;
    static int u16(const char*) noexcept;
    static std::size_t find_first_not_upper_ascii(const char* s);
};

/* ======================================================================= */
int
basic_parser::u16(const char* s) noexcept
{
    char *s_end = nullptr;
    long value = (errno=0, std::strtol(s, &s_end, 10));

    if (s_end == s || *s_end != '\0')
        return -1;
    if (errno == ERANGE)
        return -1;
    if (not (0 <= value && value <= __UINT16_MAX__))
        return -1;

    return static_cast<int>(value);
}

/* ======================================================================= */
std::size_t
basic_parser::find_first_not_upper_ascii(const char* s)
{
    const char* s_end = std::find_if_not(s, s+8, [](char c) {
        return std::isupper(c, std::locale::classic());
    });
    return static_cast<std::size_t>(s_end-s);
};

/* ======================================================================= */

} /* namespace detail */
} /* namespace zcsevcik */
} /* namespace libfatek */

#include "detail/address/lexer.inl"

#endif /* ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_BASIC_PARSER_HPP_ */
