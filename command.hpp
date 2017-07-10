/*
 * zcsevcik/libfatek/command.hpp
 *
 * Author(s):      Radek Sevcik <zcsevcik@gmail.com>
 * Date:           2017/07/05
 *
 * This file is part of zcsevcik/libfatek.
 */

#ifndef ZCSEVCIK_LIBFATEK_COMMAND_HPP_
#define ZCSEVCIK_LIBFATEK_COMMAND_HPP_

#include "address.hpp"
#include <string>
#include <utility>

namespace zcsevcik {
namespace libfatek {
/* ======================================================================= */
enum class error_code {
    error_free = 0x0,
    illegal_value = 0x2,
    illegal_format_or_communication_command_cannot_execute = 0x4,
    cannot_run_ladder_checksum_error_when_run_PLC = 0x5,
    cannot_run_plc_id_is_not_equal_ladder_id_when_run_PLC = 0x6,
    cannot_run_syntax_check_error_when_run_PLC = 0x7,
    cannot_run_function_not_supported = 0x9,
    illegal_address = 0xA,
};

/* ======================================================================= */
class station final
{
    typedef unsigned char value_type;
    value_type no_;

public:
    explicit station(value_type value)
      : no_(value)
    { }

    bool operator<(station const& rhs) const noexcept
    { return no_ < rhs.no_; }

    bool operator==(station const& rhs) const noexcept
    { return no_ == rhs.no_; }

public:
    value_type value() const noexcept
    { return no_; }

    constexpr static value_type broadcast = 0;
};

/* ======================================================================= */
class command
{
protected:
    command()
      : station_no_(1)
    { }

public:
    station const& station_no() const noexcept
    { return station_no_; }

    void station_no(station value) noexcept
    { station_no_ = std::move(value); }

    void station_no(int value) noexcept
    { station_no_ = std::move(station(value)); }

    enum class code {
        read_the_system_status_of_PLC = 0x40,
        control_the_PLC_RUN_STOP = 0x41,
        single_discrete_control = 0x42,
        the_status_reading_of_ENABLE_DISABLE_of_continuous_discrete = 0x43,
        the_status_reading_of_continuous_discrete = 0x44,
        write_the_status_to_continuous_discrete = 0x45,
        read_the_data_from_continuous_registers = 0x46,
        write_to_continuous_registers = 0x47,
        mixed_read_the_random_discrete_status_or_register_data = 0x48,
        mixed_write_the_random_discrete_status_or_register_data = 0x49,
        loop_back_testing = 0x4E,
        read_the_detailed_system_status_of_PLC = 0x53,
    };

protected:
    station station_no_;
};

/* ======================================================================= */
class command_with_address
  : public command
{
protected:
    command_with_address()
      : command()
      , start_no_()
    { }

public:
    address const& start_no() const noexcept
    { return start_no_; }

    void start_no(address value) noexcept
    { start_no_ = std::move(value); }

    bool start_no(const char* s) noexcept
    {
        bool success = false;
        return start_no_ = address::parse(s, success), success;
    }

protected:
    address start_no_;
};

/* ======================================================================= */
class command_with_continuous_address
  : public command_with_address
{
protected:
    command_with_continuous_address()
      : command_with_address()
      , addresses_count_(1)
    { }

public:
    int addresses_count() const noexcept
    { return addresses_count_; }

    void addresses_count(int value) noexcept
    { addresses_count_ = std::move(value); }

protected:
    // 1<=N<=256
    int addresses_count_;
};

/* ======================================================================= */
class loop_back_testing final
  : public command
{
public:
    constexpr static command::code command_code()
    { return command::code::loop_back_testing; }

public:
    loop_back_testing() noexcept
      : command()
      , data_()
    { }

    int dump(char* buffer, int size) const noexcept;

    loop_back_testing getResponse() const noexcept
    { return loop_back_testing(); }

    int load(const char* buffer, int size) noexcept;

public:
    std::string const& data() const noexcept
    { return data_; }

    void data(std::string value) noexcept
    { data_ = std::move(value); }

private:
    std::string data_;
};

/* ======================================================================= */
class read_the_system_status_of_PLC final
  : public command
{
public:
    constexpr static command::code command_code()
    { return command::code::read_the_system_status_of_PLC; }

public:
    read_the_system_status_of_PLC() noexcept
      : command()
    { }

    int dump(char* buffer, int size) const noexcept;
};

/* ======================================================================= */
class read_the_detailed_system_status_of_PLC final
  : public command
{
public:
    constexpr static command::code command_code()
    { return command::code::read_the_detailed_system_status_of_PLC; }

public:
    read_the_detailed_system_status_of_PLC() noexcept
      : command()
    { }

    int dump(char* buffer, int size) const noexcept;
};

/* ======================================================================= */
class control_the_PLC_RUN_STOP final
  : public command
{
public:
    constexpr static command::code command_code()
    { return command::code::control_the_PLC_RUN_STOP; }

public:
    explicit control_the_PLC_RUN_STOP() noexcept
      : command()
      , control_code_(RUN)
    { }

    int dump(char* buffer, int size) const noexcept;

public:
    enum control_code_t { STOP = 0, RUN = 1 };

    control_code_t const& control_code() const noexcept
    { return control_code_; }

    void control_code(control_code_t value) noexcept
    { control_code_ = std::move(value); }

private:
    control_code_t control_code_;
};

/* ======================================================================= */
class single_discrete_control final
  : public command_with_address
{
public:
    constexpr static command::code command_code()
    { return command::code::single_discrete_control; }

public:
    single_discrete_control() noexcept
      : command_with_address()
      , running_code_(ENABLE)
    { }

    int dump(char* buffer, int size) const noexcept;

public:
    enum running_code_t { DISABLE = 1, ENABLE = 2,
                          SET = 3, RESET = 4 };

    running_code_t const& running_code() const noexcept
    { return running_code_; }

    void running_code(running_code_t value) noexcept
    { running_code_ = std::move(value); }

private:
    running_code_t running_code_;
};

/* ======================================================================= */
class the_status_reading_of_ENABLE_DISABLE_of_continuous_discrete final
  : public command_with_continuous_address
{
public:
    constexpr static command::code command_code()
    { return command::code::the_status_reading_of_ENABLE_DISABLE_of_continuous_discrete; }

public:
    the_status_reading_of_ENABLE_DISABLE_of_continuous_discrete() noexcept
      : command_with_continuous_address()
    { }

    int dump(char* buffer, int size) const noexcept;
};

/* ======================================================================= */
class read_the_data_from_continuous_registers final
  : public command_with_continuous_address
{
public:
    constexpr static command::code command_code()
    { return command::code::read_the_data_from_continuous_registers; }

public:
    read_the_data_from_continuous_registers() noexcept
      : command_with_continuous_address()
    { }

    int dump(char* buffer, int size) const noexcept;
};

/* ======================================================================= */
class the_status_reading_of_continuous_discrete final
  : public command_with_continuous_address
{
public:
    constexpr static command::code command_code()
    { return command::code::the_status_reading_of_continuous_discrete; }

public:
    the_status_reading_of_continuous_discrete() noexcept
      : command_with_continuous_address()
    { }

    int dump(char* buffer, int size) const noexcept;
};


} /* namespace libfatek */
} /* namespace zcsevcik */
#endif  /* ZCSEVCIK_LIBFATEK_COMMAND_HPP_ */
