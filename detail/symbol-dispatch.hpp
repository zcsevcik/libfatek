/*
 * zcsevcik/libfatek/detail/symbol-dispatch.hpp
 *
 * Author(s):      Radek Sevcik <zcsevcik@gmail.com>
 * Date:           2017/06/01
 *
 * This file is part of zcsevcik/libfatek.
 */

#ifndef ZCSEVCIK_LIBFATEK_DETAIL_SYMBOL_DISPATCH_HPP_
#define ZCSEVCIK_LIBFATEK_DETAIL_SYMBOL_DISPATCH_HPP_

#include "detail/address-types.hpp"
#include "detail/symbol.hpp"
#include <cassert>
#include <functional>

namespace zcsevcik {
namespace libfatek {
namespace detail {

class dispatch final
{
public:
    dispatch(symbol const& p_tag)
      : tag(p_tag)
    { }

    template<typename R, class F, typename... Args>
    R invoke(F&& f, Args... args)
    {
        switch (tag)
        {
        default:          assert(false); break;
        case symbol::X:   return f(input_discrete{}, std::forward<Args>(args)...);
        case symbol::WX:  return f(input_discrete_16{}, std::forward<Args>(args)...);
        case symbol::DWX: return f(input_discrete_32{}, std::forward<Args>(args)...);
        case symbol::Y:   return f(output_relay{}, std::forward<Args>(args)...);
        case symbol::WY:  return f(output_relay_16{}, std::forward<Args>(args)...);
        case symbol::DWY: return f(output_relay_32{}, std::forward<Args>(args)...);
        case symbol::M:   return f(internal_relay{}, std::forward<Args>(args)...);
        case symbol::WM:  return f(internal_relay_16{}, std::forward<Args>(args)...);
        case symbol::DWM: return f(internal_relay_32{}, std::forward<Args>(args)...);
        case symbol::S:   return f(step_relay{}, std::forward<Args>(args)...);
        case symbol::WS:  return f(step_relay_16{}, std::forward<Args>(args)...);
        case symbol::DWS: return f(step_relay_32{}, std::forward<Args>(args)...);
        case symbol::T:   return f(timer_discrete{}, std::forward<Args>(args)...);
        case symbol::WT:  return f(timer_discrete_16{}, std::forward<Args>(args)...);
        case symbol::DWT: return f(timer_discrete_32{}, std::forward<Args>(args)...);
        case symbol::C:   return f(counter_discrete{}, std::forward<Args>(args)...);
        case symbol::WC:  return f(counter_discrete_16{}, std::forward<Args>(args)...);
        case symbol::DWC: return f(counter_discrete_32{}, std::forward<Args>(args)...);
        case symbol::RT:  return f(timer_register_16{}, std::forward<Args>(args)...);
        case symbol::DRT: return f(timer_register_32{}, std::forward<Args>(args)...);
        case symbol::RC:  return f(counter_register_16{}, std::forward<Args>(args)...);
        case symbol::DRC: return f(counter_register_32{}, std::forward<Args>(args)...);
        case symbol::R:   return f(data_register_hr_16{}, std::forward<Args>(args)...);
        case symbol::DR:  return f(data_register_hr_32{}, std::forward<Args>(args)...);
        case symbol::D:   return f(data_register_dr_16{}, std::forward<Args>(args)...);
        case symbol::DD:  return f(data_register_dr_32{}, std::forward<Args>(args)...);
        case symbol::F:   return f(file_register_16{}, std::forward<Args>(args)...);
        case symbol::DF:  return f(file_register_32{}, std::forward<Args>(args)...);
        }
    }

    template<class F, typename... Args>
    void invoke(F&& f, Args... args)
    {
        switch (tag)
        {
        default:          assert(false); break;
        case symbol::X:   f(input_discrete{}, std::forward<Args>(args)...);
        case symbol::WX:  f(input_discrete_16{}, std::forward<Args>(args)...);
        case symbol::DWX: f(input_discrete_32{}, std::forward<Args>(args)...);
        case symbol::Y:   f(output_relay{}, std::forward<Args>(args)...);
        case symbol::WY:  f(output_relay_16{}, std::forward<Args>(args)...);
        case symbol::DWY: f(output_relay_32{}, std::forward<Args>(args)...);
        case symbol::M:   f(internal_relay{}, std::forward<Args>(args)...);
        case symbol::WM:  f(internal_relay_16{}, std::forward<Args>(args)...);
        case symbol::DWM: f(internal_relay_32{}, std::forward<Args>(args)...);
        case symbol::S:   f(step_relay{}, std::forward<Args>(args)...);
        case symbol::WS:  f(step_relay_16{}, std::forward<Args>(args)...);
        case symbol::DWS: f(step_relay_32{}, std::forward<Args>(args)...);
        case symbol::T:   f(timer_discrete{}, std::forward<Args>(args)...);
        case symbol::WT:  f(timer_discrete_16{}, std::forward<Args>(args)...);
        case symbol::DWT: f(timer_discrete_32{}, std::forward<Args>(args)...);
        case symbol::C:   f(counter_discrete{}, std::forward<Args>(args)...);
        case symbol::WC:  f(counter_discrete_16{}, std::forward<Args>(args)...);
        case symbol::DWC: f(counter_discrete_32{}, std::forward<Args>(args)...);
        case symbol::RT:  f(timer_register_16{}, std::forward<Args>(args)...);
        case symbol::DRT: f(timer_register_32{}, std::forward<Args>(args)...);
        case symbol::RC:  f(counter_register_16{}, std::forward<Args>(args)...);
        case symbol::DRC: f(counter_register_32{}, std::forward<Args>(args)...);
        case symbol::R:   f(data_register_hr_16{}, std::forward<Args>(args)...);
        case symbol::DR:  f(data_register_hr_32{}, std::forward<Args>(args)...);
        case symbol::D:   f(data_register_dr_16{}, std::forward<Args>(args)...);
        case symbol::DD:  f(data_register_dr_32{}, std::forward<Args>(args)...);
        case symbol::F:   f(file_register_16{}, std::forward<Args>(args)...);
        case symbol::DF:  f(file_register_32{}, std::forward<Args>(args)...);
        }
    }

private:
    symbol const& tag;
};

} /* namespace detail */
} /* namespace zcsevcik */
} /* namespace libfatek */

#endif /* ZCSEVCIK_LIBFATEK_DETAIL_SYMBOL_DISPATCH_HPP_ */
