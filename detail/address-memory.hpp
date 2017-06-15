/*
 * zcsevcik/libfatek/detail/address-memory.hpp
 *
 * Author(s):      Radek Sevcik <zcsevcik@gmail.com>
 * Date:           2017/06/02
 *
 * This file is part of zcsevcik/libfatek.
 */

#ifndef ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_MEMORY_HPP_
#define ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_MEMORY_HPP_

#include <cerrno>
#include <cstdlib>

namespace zcsevcik {
namespace libfatek {
namespace detail {

struct memory final
{
public:
    struct contiguous {};
    struct alignas_8 {};

public:
    template<class T>
    constexpr static bool is_aligned(contiguous, T) noexcept
    { return true; }

    template<class T>
    constexpr static bool is_aligned(alignas_8, T addr) noexcept
    { return addr % 8 == 0; }

public:
    static int u16_TryParse(const char* s) noexcept;
};

int memory::u16_TryParse(const char* s) noexcept
{
    errno = 0;
    char *s_end = nullptr;
    long value = std::strtol(s, &s_end, 10);

    if (s_end == s || *s_end != '\0')
        return -1;
    if (errno == ERANGE)
        return -1;
    if (not (0 <= value && value <= __UINT16_MAX__))
        return -1;

    return static_cast<int>(value);
}

} /* namespace detail */
} /* namespace zcsevcik */
} /* namespace libfatek */

#endif /* ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_MEMORY_HPP_ */
