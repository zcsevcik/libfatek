/*
 * zcsevcik/libfatek/t-command.cpp
 *
 * Author(s):      Radek Sevcik <zcsevcik@gmail.com>
 * Date:           2017/07/05
 *
 * This file is part of zcsevcik/libfatek.
 */

#include "command.hpp"
#include "gtest/gtest.h"

using namespace zcsevcik::libfatek;
/* ======================================================================= */
void check_command_dump(command const& cmd, const char* expected)
{
    char dump[512] = { 0 };
    int const dump_result = cmd.dump(dump, sizeof dump);

    bool const no_error = dump_result > 0;
    bool const buffer_too_small = dump_result >= static_cast<int>(sizeof dump);

    ASSERT_EQ(true, no_error and not buffer_too_small);
    ASSERT_STREQ(expected, dump);
}

/* ======================================================================= */
TEST(command, loop_back_testing)
{
//    constexpr const char expected_response_dump[] = "\x02""01""4E""ABCDEFG""B8""\x03";

    loop_back_testing req;
    req.station_no(1);
    req.data("ABCDEFG");

    check_command_dump(req, "\x02""01""4E""ABCDEFG""B8""\x03");
}

/* ======================================================================= */
TEST(command, read_the_system_status_of_PLC)
{
//    constexpr const char expected_response_dump[] = "\x02""01""40""0""290000""22""\x03";

    read_the_system_status_of_PLC req;
    req.station_no(1);

    check_command_dump(req, "\x02""01""40""C7""\x03");
}

/* ======================================================================= */
TEST(command, read_the_detailed_system_status_of_PLC)
{
//    constexpr const char expected_response_dump[] = "\x02""01""53""0""210102408000010001000064006407D203E800001F""88""\x03";

    read_the_detailed_system_status_of_PLC req;
    req.station_no(1);

    check_command_dump(req, "\x02""01""53""CB""\x03");
}

/* ======================================================================= */
TEST(command, control_the_PLC_RUN_STOP)
{
//    constexpr const char expected_response_dump[] = "\x02""01""41""0""F8""\x03";

    control_the_PLC_RUN_STOP req;
    req.station_no(1);
    req.control_code(control_the_PLC_RUN_STOP::RUN);

    check_command_dump(req, "\x02""01""41""1""F9""\x03");
}

/* ======================================================================= */
TEST(command, single_discrete_control)
{
//    constexpr const char expected_response_dump[] = "\x02""01""42""0""F9""\x03";

    single_discrete_control req;
    req.station_no(1);
    req.running_code(single_discrete_control::DISABLE);
    req.start_no("X16");

    check_command_dump(req, "\x02""01""42""1""X0016""19""\x03");
}

/* ======================================================================= */
TEST(command, the_status_reading_of_ENABLE_DISABLE_of_continuous_discrete)
{
//    constexpr const char expected_response_dump[] = "\x02""01""43""0""1010001""4D""\x03";

    the_status_reading_of_ENABLE_DISABLE_of_continuous_discrete req;
    req.station_no(1);
    req.start_no("Y10");
    req.addresses_count(7);

    check_command_dump(req, "\x02""01""43""07""Y0010""4B""\x03");
}

/* ======================================================================= */
TEST(command, read_the_data_from_continuous_registers)
{
//    constexpr const char expected_response_dump[] = "\x02""01""46""0""10A5""7FC4""0001""89""\x03";

    read_the_data_from_continuous_registers req;
    req.station_no(1);
    req.start_no("R12");
    req.addresses_count(3);

    check_command_dump(req, "\x02""01""46""03""R00012""75""\x03");
}

/* ======================================================================= */
TEST(command, the_status_reading_of_continuous_discrete)
{
//    constexpr const char expected_response_dump[] = "\x02""01""44""0""010110""1E""\x03";

    the_status_reading_of_continuous_discrete req;
    req.station_no(1);
    req.start_no("X50");
    req.addresses_count(6);

    check_command_dump(req, "\x02""01""44""06""X0050""4E""\x03");
}
