/*
 * zcsevcik/libfatek/detail/command/occupancy.hpp
 *
 * Author(s):      Radek Sevcik <zcsevcik@gmail.com>
 * Date:           2017/08/07
 *
 * This file is part of zcsevcik/libfatek.
 */

#ifndef ZCSEVCIK_LIBFATEK_DETAIL_OCCUPANCY_HPP_
#define ZCSEVCIK_LIBFATEK_DETAIL_OCCUPANCY_HPP_

#include "address.hpp"
#include "command.hpp"
#include "detail/command/frame.hpp"
#include "detail/command/checksum.hpp"
#include <cstring>
#include <string>

namespace zcsevcik {
namespace libfatek {
namespace detail {
/* ======================================================================= */
struct occupancy final
{
    constexpr int operator()(unsigned char) const noexcept
    { return 2; }

    constexpr int operator()(STX) const noexcept
    { return 1; }

    constexpr int operator()(ETX) const noexcept
    { return 1; }

    constexpr int operator()(station const&) const noexcept
    { return 2; }

    constexpr int operator()(command_code_t) const noexcept
    { return 2; }

    constexpr int operator()(error_code_t) const noexcept
    { return 1; }

    constexpr int operator()(control_the_PLC_RUN_STOP::control_code_t) const noexcept
    { return 1; }

    constexpr int operator()(single_discrete_control::running_code_t) const noexcept
    { return 1; }

    constexpr int operator()(checksum const&) const noexcept
    { return 2; }

    int operator()(std::string const& s) const noexcept
    { return s.length(); }

    int operator()(address const& a) const noexcept
    { return std::strlen(a.dump()); }
};

} /* namespace detail */
} /* namespace zcsevcik */
} /* namespace libfatek */

#endif /* ZCSEVCIK_LIBFATEK_DETAIL_BYTE_OCCUPANCY_HPP_ */
