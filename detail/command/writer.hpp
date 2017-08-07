/*
 * zcsevcik/libfatek/detail/command/writer.hpp
 *
 * Author(s):      Radek Sevcik <zcsevcik@gmail.com>
 * Date:           2017/08/07
 *
 * This file is part of zcsevcik/libfatek.
 */

#include "address.hpp"
#include "command.hpp"
#include "detail/command/checksum.hpp"
#include "detail/command/frame.hpp"
#include <string>
#include <cstring>

#ifndef ZCSEVCIK_LIBFATEK_DETAIL_COMMAND_WRITER_HPP_
#define ZCSEVCIK_LIBFATEK_DETAIL_COMMAND_WRITER_HPP_

namespace zcsevcik {
namespace libfatek {
namespace detail {

class writer final
{
public:
    writer(char** buffer_)
      : buffer(*buffer_)
    { }

    ~writer()
    { *buffer = '\0'; }

    writer(writer const&) = delete;
    writer& operator=(writer const&) = delete;
    writer(writer &&) = delete;
    writer& operator=(writer &&) = delete;

    template<typename T>
    writer& operator<<(T&& t) noexcept
    {
        this->operator()(std::forward<T>(t));
        return *this;
    }

    void operator()(unsigned char c) noexcept
    { byte(c); }

    void operator()(STX) noexcept
    { *buffer++ = '\x02'; }

    void operator()(ETX) noexcept
    { *buffer++ = '\x03'; }

    void operator()(station const& station_no) noexcept
    { byte(static_cast<unsigned char>( station_no.value() )); }

    void operator()(command_code_t cc) noexcept
    { byte(static_cast<unsigned char>(cc)); }

    void operator()(error_code_t ec) noexcept
    { nibble(static_cast<unsigned char>(ec)); }

    void operator()(control_the_PLC_RUN_STOP::control_code_t cc) noexcept
    { nibble(static_cast<unsigned char>(cc)); }

    void operator()(single_discrete_control::running_code_t rc) noexcept
    { nibble(static_cast<unsigned char>(rc)); }

    void operator()(checksum const& lrc) noexcept
    { *buffer = '\0', byte(lrc()); }

    void operator()(std::string const& s) noexcept
    {
        s.copy(buffer, std::string::npos);
        buffer += s.length();
    }

    void operator()(address const& a) noexcept
    {
#ifdef HAVE_STPCPY
        buffer = stpcpy(buffer, a.dump());
#else
        std::strcpy(buffer, a.dump());
        buffer += std::strlen(buffer);
#endif
    }

private:
    void byte(unsigned char c) noexcept
    { nibble(c >> 4), nibble(c >> 0); }

    void nibble(unsigned char c) noexcept
    { *buffer++ = "0123456789ABCDEF"[c & 0x0f]; }

private:
    char*& buffer;
};


} /* namespace detail */
} /* namespace zcsevcik */
} /* namespace libfatek */

#endif /* ZCSEVCIK_LIBFATEK_DETAIL_COMMAND_WRITER_HPP_ */
