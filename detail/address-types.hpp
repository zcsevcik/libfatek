/*
 * zcsevcik/libfatek/detail/address-types.hpp
 *
 * Author(s):      Radek Sevcik <zcsevcik@gmail.com>
 * Date:           2017/06/02
 *
 * This file is part of zcsevcik/libfatek.
 */

#ifndef ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_TYPES_HPP_
#define ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_TYPES_HPP_

namespace zcsevcik {
namespace libfatek {
namespace detail {

struct counter_discrete {};
struct counter_discrete_16 {};
struct counter_discrete_32 {};
struct counter_register_16 {};
struct counter_register_32 {};
struct data_register_dr_16 {};
struct data_register_dr_32 {};
struct data_register_hr_16 {};
struct data_register_hr_32 {};
struct file_register_16 {};
struct file_register_32 {};
struct input_discrete {};
struct input_discrete_16 {};
struct input_discrete_32 {};
struct internal_relay {};
struct internal_relay_16 {};
struct internal_relay_32 {};
struct output_relay {};
struct output_relay_16 {};
struct output_relay_32 {};
struct step_relay {};
struct step_relay_16 {};
struct step_relay_32 {};
struct timer_discrete {};
struct timer_discrete_16 {};
struct timer_discrete_32 {};
struct timer_register_16 {};
struct timer_register_32 {};

} /* namespace detail */
} /* namespace zcsevcik */
} /* namespace libfatek */

#endif /* ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_TYPES_HPP_ */
