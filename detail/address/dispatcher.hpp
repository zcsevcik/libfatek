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

template<typename R, typename... Args>
class dispatcher final
{
    std::function<R(Args...)> invoke;

public:
    R operator()(Args... args) const {
        return invoke(std::forward<Args>(args)...);
    }

public:
    template<typename F>
    dispatcher(address::symbol_t tag, F&& f)
      : invoke( )
    {
        switch (tag)
        {
        default:           assert(false); break;
        case address::X:   invoke = std::bind(&F::X, std::forward<F>(f)); break;
        case address::WX:  invoke = std::bind(&F::WX, std::forward<F>(f)); break;
        case address::DWX: invoke = std::bind(&F::DWX, std::forward<F>(f)); break;
        case address::Y:   invoke = std::bind(&F::Y, std::forward<F>(f)); break;
        case address::WY:  invoke = std::bind(&F::WY, std::forward<F>(f)); break;
        case address::DWY: invoke = std::bind(&F::DWY, std::forward<F>(f)); break;
        case address::M:   invoke = std::bind(&F::M, std::forward<F>(f)); break;
        case address::WM:  invoke = std::bind(&F::WM, std::forward<F>(f)); break;
        case address::DWM: invoke = std::bind(&F::DWM, std::forward<F>(f)); break;
        case address::S:   invoke = std::bind(&F::S, std::forward<F>(f)); break;
        case address::WS:  invoke = std::bind(&F::WS, std::forward<F>(f)); break;
        case address::DWS: invoke = std::bind(&F::DWS, std::forward<F>(f)); break;
        case address::T:   invoke = std::bind(&F::T, std::forward<F>(f)); break;
        case address::WT:  invoke = std::bind(&F::WT, std::forward<F>(f)); break;
        case address::DWT: invoke = std::bind(&F::DWT, std::forward<F>(f)); break;
        case address::C:   invoke = std::bind(&F::C, std::forward<F>(f)); break;
        case address::WC:  invoke = std::bind(&F::WC, std::forward<F>(f)); break;
        case address::DWC: invoke = std::bind(&F::DWC, std::forward<F>(f)); break;
        case address::RT:  invoke = std::bind(&F::RT, std::forward<F>(f)); break;
        case address::DRT: invoke = std::bind(&F::DRT, std::forward<F>(f)); break;
        case address::RC:  invoke = std::bind(&F::RC, std::forward<F>(f)); break;
        case address::DRC: invoke = std::bind(&F::DRC, std::forward<F>(f)); break;
        case address::R:   invoke = std::bind(&F::R, std::forward<F>(f)); break;
        case address::DR:  invoke = std::bind(&F::DR, std::forward<F>(f)); break;
        case address::D:   invoke = std::bind(&F::D, std::forward<F>(f)); break;
        case address::DD:  invoke = std::bind(&F::DD, std::forward<F>(f)); break;
        case address::F:   invoke = std::bind(&F::F, std::forward<F>(f)); break;
        case address::DF:  invoke = std::bind(&F::DF, std::forward<F>(f)); break;
        }
    }
};

} /* namespace detail */
} /* namespace zcsevcik */
} /* namespace libfatek */

#endif /* ZCSEVCIK_LIBFATEK_DETAIL_ADDRESS_DISPATCHER_HPP_ */
