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
    char value[8];

public:
    enum symbol_t {
    // X: Input discrete
        X, WX, DWX,
    // Y: Output relay
        Y, WY, DWY,
    // M: Internal relay
        M, WM, DWM,
    // S: Step relay
        S, WS, DWS,
    // T: Timer discrete
        T, WT, DWT,
    // C: Counter discrete
        C, WC, DWC,
    // TMR: Timer register
           RT, DRT,
    // CTR: Counter register
           RC, DRC,
    // HR: Data register
            R,  DR,
    // DR: Data register
            D,  DD,
    // FR: File register
            F,  DF,
    };

public:
    address() noexcept;
    static address parse(const char*, bool&) noexcept;
    const char* dump() const noexcept;

    symbol_t symbol() const noexcept;
    constexpr static auto invalid_symbol = static_cast<symbol_t>(-1);

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
