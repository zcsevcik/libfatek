/*
 * zcsevcik/libfatek/address.hpp
 *
 * Author(s):      Radek Sevcik <zcsevcik@gmail.com>
 * Date:           2017/05/24
 *
 * This file is part of zcsevcik/libfatek.
 */

#ifndef ZCSEVCIK_LIBFATEK_ADDRESS_HPP_
#define ZCSEVCIK_LIBFATEK_ADDRESS_HPP_

namespace zcsevcik {
namespace libfatek {

class address final
{
private:
    char value[8];

public:
    address() noexcept;
    static address parse(const char*, bool&) noexcept;
    const char* dump() const noexcept;

public:
    bool is_discrete_address() const noexcept;
    bool is_register_16_address() const noexcept;
    bool is_register_32_address() const noexcept;

    bool is_input_discrete() const noexcept;
    bool is_output_relay() const noexcept;
    bool is_internal_relay() const noexcept;
    bool is_step_relay() const noexcept;
    bool is_timer_discrete() const noexcept;
    bool is_counter_discrete() const noexcept;
    bool is_timer_register() const noexcept;
    bool is_counter_register() const noexcept;
    bool is_data_register_hr() const noexcept;
    bool is_data_register_dr() const noexcept;
    bool is_file_register() const noexcept;
};

} /* namespace libfatek */
} /* namespace zcsevcik */

#endif /* ZCSEVCIK_LIBFATEK_ADDRESS_HPP_ */
