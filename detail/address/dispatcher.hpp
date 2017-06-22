/*
 * zcsevcik/libfatek/detail/address/dispatcher.hpp
 *
 * Author(s):      Radek Sevcik <zcsevcik@gmail.com>
 * Date:           2017/06/20
 *
 * This file is part of zcsevcik/libfatek.
 */

#ifndef ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_DISPATCHER_HPP_
#define ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_DISPATCHER_HPP_

#include "address.hpp"
#include <cassert>
#include <functional>

namespace zcsevcik {
namespace libfatek {
namespace detail {

template<typename R, class T, typename... Args>
class dispatcher final
{
    std::function<R(Args...)> invoke;

public:
    R operator()(Args... args) const {
        return invoke(std::forward<Args>(args)...);
    }

public:
    dispatcher(address::symbol_t tag)
      : invoke( )
    {
        switch (tag)
        {
        default:           assert(false); break;
        case address::X:   invoke = &T::X; break;
        case address::WX:  invoke = &T::WX; break;
        case address::DWX: invoke = &T::DWX; break;
        case address::Y:   invoke = &T::Y; break;
        case address::WY:  invoke = &T::WY; break;
        case address::DWY: invoke = &T::DWY; break;
        case address::M:   invoke = &T::M; break;
        case address::WM:  invoke = &T::WM; break;
        case address::DWM: invoke = &T::DWM; break;
        case address::S:   invoke = &T::S; break;
        case address::WS:  invoke = &T::WS; break;
        case address::DWS: invoke = &T::DWS; break;
        case address::T:   invoke = &T::T; break;
        case address::WT:  invoke = &T::WT; break;
        case address::DWT: invoke = &T::DWT; break;
        case address::C:   invoke = &T::C; break;
        case address::WC:  invoke = &T::WC; break;
        case address::DWC: invoke = &T::DWC; break;
        case address::RT:  invoke = &T::RT; break;
        case address::DRT: invoke = &T::DRT; break;
        case address::RC:  invoke = &T::RC; break;
        case address::DRC: invoke = &T::DRC; break;
        case address::R:   invoke = &T::R; break;
        case address::DR:  invoke = &T::DR; break;
        case address::D:   invoke = &T::D; break;
        case address::DD:  invoke = &T::DD; break;
        case address::F:   invoke = &T::F; break;
        case address::DF:  invoke = &T::DF; break;
        }
    }
};

} /* namespace detail */
} /* namespace zcsevcik */
} /* namespace libfatek */

#endif /* ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_DISPATCHER_HPP_ */
