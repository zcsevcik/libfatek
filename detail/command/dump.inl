/*
 * zcsevcik/libfatek/detail/dump.inl
 *
 * Author(s):      Radek Sevcik <zcsevcik@gmail.com>
 * Date:           2017/07/06
 *
 * This file is part of zcsevcik/libfatek.
 */

#include "command.hpp"
#include "detail/command/frame.hpp"

namespace zcsevcik {
namespace libfatek {
namespace detail {
/* ======================================================================= */
template<class T, typename... Args>
static int
dump_internal(char* buffer, int bufsize, T& cmd, Args&&... args) noexcept
{
    using namespace detail;
    count_bytes size{};
    checksum LRC{buffer};

    const int hdrlen = size(STX{}) + size(cmd.station_no())
                     + size(cmd.command_code()) + size(LRC) + size(ETX{});
    const int payload = (( 0 + ... + size(args) ));
    const int framelen = hdrlen + payload;

    if (buffer == nullptr)      return -1;
    if (bufsize < 0)            return -1;
    if (bufsize <= framelen)    return framelen+1;

    char* buffer_end = buffer;
    writer wr(&buffer_end);

    wr << STX{} << cmd.station_no() << cmd.command_code();
    (void) ((wr << ... << args));
    wr << LRC << ETX{};
    return buffer_end - buffer;
}

static int
to_number_n(int address_count) noexcept
{
    if      (address_count <=   0)  { return -1; }
    else if (address_count  > 256)  { return -1; }
    else if (address_count == 256)  { return 0; }
    else                            { return address_count; }
}

} /* namespace detail */
/* ======================================================================= */
int loop_back_testing
        ::dump(char* buffer, int size) const noexcept
{
    return detail::dump_internal(buffer, size, *this,
            data());
}

int read_the_system_status_of_PLC
        ::dump(char* buffer, int size) const noexcept
{
    return detail::dump_internal(buffer, size, *this);
}

int read_the_detailed_system_status_of_PLC
        ::dump(char* buffer, int size) const noexcept
{
    return detail::dump_internal(buffer, size, *this);
}

int control_the_PLC_RUN_STOP
        ::dump(char* buffer, int size) const noexcept
{
    return detail::dump_internal(buffer, size, *this,
            control_code());
}

int single_discrete_control
        ::dump(char* buffer, int size) const noexcept
{
    if (not start_no().is_discrete_address())
        return -1;

    return detail::dump_internal(buffer, size, *this,
            running_code(), start_no());
}

int the_status_reading_of_ENABLE_DISABLE_of_continuous_discrete
        ::dump(char* buffer, int size) const noexcept
{
    int count = detail::to_number_n(addresses_count());
    if (count == -1)
        return -1;
    if (not start_no().is_discrete_address())
        return -1;

    return detail::dump_internal(buffer, size, *this,
            (unsigned char)count, start_no());
}

int read_the_data_from_continuous_registers
        ::dump(char* buffer, int size) const noexcept
{
    int count = detail::to_number_n(addresses_count());
    if (count == -1)
        return -1;

    if (not start_no().is_register_16_address() and
        not start_no().is_register_32_address())
    {
        return -1;
    }

    return detail::dump_internal(buffer, size, *this,
            (unsigned char)count, start_no());
}

int the_status_reading_of_continuous_discrete
        ::dump(char* buffer, int size) const noexcept
{
    int count = detail::to_number_n(addresses_count());
    if (count == -1)
        return -1;
    if (not start_no().is_discrete_address())
        return -1;

    return detail::dump_internal(buffer, size, *this,
            (unsigned char)count, start_no());
}


} /* namespace libfatek */
} /* namespace zcsevcik */
