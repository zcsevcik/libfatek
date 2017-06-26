/*
 * zcsevcik/libfatek/t-address.cpp
 *
 * Author(s):      Radek Sevcik <zcsevcik@gmail.com>
 * Date:           2017/06/02
 *
 * This file is part of zcsevcik/libfatek.
 */

#include "address.hpp"
#include "gtest/gtest.h"
#include <cstdio>

using namespace zcsevcik::libfatek;
/* ======================================================================= */
TEST(address, default_is_empty) {
    address a;
    ASSERT_STREQ("", a.dump());
    ASSERT_EQ(0, a.is_discrete_address());
    ASSERT_EQ(0, a.is_register_16_address());
    ASSERT_EQ(0, a.is_register_32_address());
    ASSERT_EQ(0, a.is_input_discrete());
    ASSERT_EQ(0, a.is_output_relay());
    ASSERT_EQ(0, a.is_internal_relay());
    ASSERT_EQ(0, a.is_step_relay());
    ASSERT_EQ(0, a.is_timer_discrete());
    ASSERT_EQ(0, a.is_counter_discrete());
    ASSERT_EQ(0, a.is_timer_register());
    ASSERT_EQ(0, a.is_counter_register());
    ASSERT_EQ(0, a.is_data_register_hr());
    ASSERT_EQ(0, a.is_data_register_dr());
    ASSERT_EQ(0, a.is_file_register());
}

/* ======================================================================= */
#define test_dump(adr, str, ...)                            \
TEST(address, adr##_dump) {                                 \
    bool success = false;                                   \
    address a = address::parse(#adr, success);              \
    ASSERT_EQ(success, true);                               \
    ASSERT_STREQ(str, a.dump());                            \
}

#define test_props(adr, str, discr, reg16, reg32, X, Y, M, S, T, C, TMR, CTR, HR, DR, FR, ...) \
TEST(address, adr##_props) {                                \
    bool success = false;                                   \
    address a = address::parse(#adr, success);              \
    ASSERT_EQ(success, true);                               \
    ASSERT_EQ(discr, a.is_discrete_address());              \
    ASSERT_EQ(reg16, a.is_register_16_address());           \
    ASSERT_EQ(reg32, a.is_register_32_address());           \
    ASSERT_EQ(X, a.is_input_discrete());                    \
    ASSERT_EQ(Y, a.is_output_relay());                      \
    ASSERT_EQ(M, a.is_internal_relay());                    \
    ASSERT_EQ(S, a.is_step_relay());                        \
    ASSERT_EQ(T, a.is_timer_discrete());                    \
    ASSERT_EQ(C, a.is_counter_discrete());                  \
    ASSERT_EQ(TMR, a.is_timer_register());                  \
    ASSERT_EQ(CTR, a.is_counter_register());                \
    ASSERT_EQ(HR, a.is_data_register_hr());                 \
    ASSERT_EQ(DR, a.is_data_register_dr());                 \
    ASSERT_EQ(FR, a.is_file_register());                    \
}

#define X(_, ...) \
    _(  X0,   "X0000", 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ##__VA_ARGS__) \
    _(  Y0,   "Y0000", 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, ##__VA_ARGS__) \
    _(  M0,   "M0000", 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, ##__VA_ARGS__) \
    _(  S0,   "S0000", 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ##__VA_ARGS__) \
    _(  T0,   "T0000", 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, ##__VA_ARGS__) \
    _(  C0,   "C0000", 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, ##__VA_ARGS__) \
    _( WX0,  "WX0000", 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ##__VA_ARGS__) \
    _( WY0,  "WY0000", 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, ##__VA_ARGS__) \
    _( WM0,  "WM0000", 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, ##__VA_ARGS__) \
    _( WS0,  "WS0000", 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ##__VA_ARGS__) \
    _( WT0,  "WT0000", 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, ##__VA_ARGS__) \
    _( WC0,  "WC0000", 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, ##__VA_ARGS__) \
    _( RT0,  "RT0000", 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, ##__VA_ARGS__) \
    _( RC0,  "RC0000", 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, ##__VA_ARGS__) \
    _(  R0,  "R00000", 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, ##__VA_ARGS__) \
    _(  D0,  "D00000", 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, ##__VA_ARGS__) \
    _(  F0,  "F00000", 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, ##__VA_ARGS__) \
    _(DWX0, "DWX0000", 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ##__VA_ARGS__) \
    _(DWY0, "DWY0000", 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, ##__VA_ARGS__) \
    _(DWM0, "DWM0000", 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, ##__VA_ARGS__) \
    _(DWS0, "DWS0000", 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ##__VA_ARGS__) \
    _(DWT0, "DWT0000", 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, ##__VA_ARGS__) \
    _(DWC0, "DWC0000", 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, ##__VA_ARGS__) \
    _(DRT0, "DRT0000", 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, ##__VA_ARGS__) \
    _(DRC0, "DRC0000", 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, ##__VA_ARGS__) \
    _( DR0, "DR00000", 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, ##__VA_ARGS__) \
    _( DD0, "DD00000", 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, ##__VA_ARGS__) \
    _( DF0, "DF00000", 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, ##__VA_ARGS__) \

X(test_dump)
X(test_props)
#undef X
#undef test_props
#undef test_dump

/* ======================================================================= */
#define test_highest_address(adr, max_addr, ...)                          \
TEST(address, adr##max_addr##_is_highest_address)                         \
{                                                                         \
    bool success = false;                                                 \
    ASSERT_EQ((address::parse(#adr #max_addr, success), success), true);  \
                                                                          \
    char buf[16]; std::snprintf(buf, sizeof buf, #adr "%u", 8u+max_addr); \
    ASSERT_EQ((address::parse(buf, success), success), false);            \
}

#define X(_, ...) \
    _(X, 9999, ##__VA_ARGS__) \
    _(Y, 9999, ##__VA_ARGS__) \
    _(M, 9999, ##__VA_ARGS__) \
    _(S, 9999, ##__VA_ARGS__) \
    _(T, 9999, ##__VA_ARGS__) \
    _(C, 9999, ##__VA_ARGS__) \
    _(WX, 9984, ##__VA_ARGS__) \
    _(WY, 9984, ##__VA_ARGS__) \
    _(WM, 9984, ##__VA_ARGS__) \
    _(WS, 9984, ##__VA_ARGS__) \
    _(WT, 9984, ##__VA_ARGS__) \
    _(WC, 9984, ##__VA_ARGS__) \
    _(RT, 9999, ##__VA_ARGS__) \
    _(RC, 9999, ##__VA_ARGS__) \
    _(R, 65535, ##__VA_ARGS__) \
    _(D, 65535, ##__VA_ARGS__) \
    _(F, 65535, ##__VA_ARGS__) \
    _(DWX, 9968, ##__VA_ARGS__) \
    _(DWY, 9968, ##__VA_ARGS__) \
    _(DWM, 9968, ##__VA_ARGS__) \
    _(DWS, 9968, ##__VA_ARGS__) \
    _(DWT, 9968, ##__VA_ARGS__) \
    _(DWC, 9968, ##__VA_ARGS__) \
    _(DRT, 9998, ##__VA_ARGS__) \
    _(DRC, 9998, ##__VA_ARGS__) \
    _(DR, 65534, ##__VA_ARGS__) \
    _(DD, 65534, ##__VA_ARGS__) \
    _(DF, 65534, ##__VA_ARGS__) \

X(test_highest_address)
#undef X
#undef test_highest_address

/* ======================================================================= */
#define test_alignment(adr, ...)                                     \
TEST(address, adr##_alignas_8)                                       \
{                                                                    \
    bool success = false;                                            \
    ASSERT_EQ((address::parse(#adr "7", success),  success), false); \
    ASSERT_EQ((address::parse(#adr "8", success),  success), true);  \
    ASSERT_EQ((address::parse(#adr "9", success),  success), false); \
    ASSERT_EQ((address::parse(#adr "15", success), success), false); \
    ASSERT_EQ((address::parse(#adr "16", success), success), true);  \
    ASSERT_EQ((address::parse(#adr "17", success), success), false); \
}

#define X(_, ...) \
    _(WX, ##__VA_ARGS__) \
    _(WY, ##__VA_ARGS__) \
    _(WM, ##__VA_ARGS__) \
    _(WS, ##__VA_ARGS__) \
    _(WT, ##__VA_ARGS__) \
    _(WC, ##__VA_ARGS__) \
    _(DWX, ##__VA_ARGS__) \
    _(DWY, ##__VA_ARGS__) \
    _(DWM, ##__VA_ARGS__) \
    _(DWS, ##__VA_ARGS__) \
    _(DWT, ##__VA_ARGS__) \
    _(DWC, ##__VA_ARGS__) \

X(test_alignment)
#undef X
#undef test_alignment

/* ======================================================================= */
TEST(address, missing_number_fails)
{
    bool success = false;
    ASSERT_EQ((address::parse("DWX", success), success), false);
}

TEST(address, unexpected_characters_after_number_fails)
{
    bool success = false;
    ASSERT_EQ((address::parse("DWX2048Y", success), success), false);
}

TEST(address, too_big_number_fails)
{
    bool success = false;
    ASSERT_EQ((address::parse("DWX18446744073709551615", success), success), false);
}

TEST(address, numbers_with_sign_fails)
{
    bool success = false;
    ASSERT_EQ((address::parse("X+8", success), success), false);
    ASSERT_EQ((address::parse("X-8", success), success), false);
}
