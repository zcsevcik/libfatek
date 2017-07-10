/*
 * zcsevcik/libfatek/detail/command/checksum.hpp
 *
 * Author(s):      Radek Sevcik <zcsevcik@gmail.com>
 * Date:           2017/07/08
 *
 * This file is part of zcsevcik/libfatek.
 */

#ifndef ZCSEVCIK_LIBFATEK_DETAIL_COMMAND_CHECKSUM_HPP_
#define ZCSEVCIK_LIBFATEK_DETAIL_COMMAND_CHECKSUM_HPP_

namespace zcsevcik {
namespace libfatek {
namespace detail {

class checksum final
{
public:
    typedef unsigned char value_type;
    checksum(const char *s_) : s(s_) { }

    value_type operator()() const noexcept
    {
        value_type sum8 = 0;
        for (const char* p = s; *p != '\0'; ++p)
            sum8 += static_cast<value_type>(*p);
        return sum8;
    }

private:
    const char* s;
};


} /* namespace detail */
} /* namespace zcsevcik */
} /* namespace libfatek */

#endif /* ZCSEVCIK_LIBFATEK_DETAIL_COMMAND_CHECKSUM_HPP_ */
