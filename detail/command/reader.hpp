/*
 * zcsevcik/libfatek/detail/command/reader.hpp
 *
 * Author(s):      Radek Sevcik <zcsevcik@gmail.com>
 * Date:           2017/08/07
 *
 * This file is part of zcsevcik/libfatek.
 */

#ifndef ZCSEVCIK_LIBFATEK_DETAIL_COMMAND_READER_HPP_
#define ZCSEVCIK_LIBFATEK_DETAIL_COMMAND_READER_HPP_

#include "address.hpp"
#include "command.hpp"
#include "detail/command/occupancy.hpp"
#include "detail/command/checksum.hpp"
#include "detail/command/frame.hpp"

namespace zcsevcik {
namespace libfatek {
namespace detail {
/* ======================================================================= */
struct reader final
{
public:
    reader(const char** buffer_)
      : buffer(*buffer_)
    { }

private:
    const char*& buffer;
};

/* ======================================================================= */

} /* namespace detail */
} /* namespace zcsevcik */
} /* namespace libfatek */

#endif /* ZCSEVCIK_LIBFATEK_DETAIL_COMMAND_READER_HPP_ */
