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
enum class error_code_t {
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
enum class command_code_t {
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

/* ======================================================================= */
class station final
{
    typedef unsigned char value_type;
    value_type no_;

public:
    station(value_type value)
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
#define PROPERTY(name, type, default_value) \
public: \
    type const& name() const noexcept { return name##_; } \
    void name(type value) noexcept { name##_ = std::move(value); } \
protected: \
    type name##_ = (default_value); \
private:

#define COMMAND_CODE(value) \
public: constexpr static command_code_t command_code() { return command_code_t::value; } \
private:

#define PROPERTY_ADDRESS(name) \
PROPERTY(name, address, address()) \
public: \
    bool name(const char* s) noexcept { \
        bool success = false; \
        return name##_ = address::parse(s, success), success; \
    } \
private:

/* ======================================================================= */
class command
{
protected:
    command() = default;
public:
    command(command const&) = default;
    command& operator=(command const&) = default;
    command(command &&) = default;
    command& operator=(command &&) = default;
    virtual ~command() = default;
public:
    virtual int dump(char* buffer, int size) const noexcept = 0;
};

class response
{
protected:
    response() = default;
public:
    response(response const&) = default;
    response& operator=(response const&) = default;
    response(response &&) = default;
    response& operator=(response &&) = default;
    virtual ~response() = default;
public:
    virtual int load(char const* buffer, int size) noexcept = 0;
};

/* ======================================================================= */
class loop_back_testing final : public command, public response
{
    COMMAND_CODE(loop_back_testing)
    PROPERTY(station_no, station, station(1))
    PROPERTY(data, std::string, std::string())

public:
    virtual int dump(char* buffer, int size) const noexcept override;
    virtual int load(char const*, int) noexcept override { return -1; }
};

/* ======================================================================= */
class read_the_system_status_of_PLC final : public command
{
    COMMAND_CODE(read_the_system_status_of_PLC)
    PROPERTY(station_no, station, station(1))

public:
    virtual int dump(char* buffer, int size) const noexcept override;
};

/* ======================================================================= */
class read_the_detailed_system_status_of_PLC final : public command
{
    COMMAND_CODE(read_the_detailed_system_status_of_PLC)
    PROPERTY(station_no, station, station(1))

public:
    virtual int dump(char* buffer, int size) const noexcept override;
};

/* ======================================================================= */
class control_the_PLC_RUN_STOP final : public command
{
public:
    enum control_code_t { STOP = 0, RUN = 1 };

    COMMAND_CODE(control_the_PLC_RUN_STOP)
    PROPERTY(station_no, station, station(1))
    PROPERTY(control_code, enum control_code_t, RUN)

public:
    virtual int dump(char* buffer, int size) const noexcept override;
};

/* ======================================================================= */
class single_discrete_control final : public command
{
public:
    enum running_code_t { DISABLE = 1, ENABLE = 2,
                          SET = 3, RESET = 4 };

    COMMAND_CODE(single_discrete_control)
    PROPERTY(station_no, station, station(1))
    PROPERTY_ADDRESS(start_no)
    PROPERTY(running_code, enum running_code_t, ENABLE)

public:
    virtual int dump(char* buffer, int size) const noexcept override;
};

/* ======================================================================= */
class the_status_reading_of_ENABLE_DISABLE_of_continuous_discrete final : public command
{
    COMMAND_CODE(the_status_reading_of_ENABLE_DISABLE_of_continuous_discrete)
    PROPERTY(station_no, station, station(1))
    PROPERTY_ADDRESS(start_no)
    PROPERTY(addresses_count, int, 1)   // 1<=N<=256

public:
    virtual int dump(char* buffer, int size) const noexcept override;
};

/* ======================================================================= */
class read_the_data_from_continuous_registers final : public command
{
    COMMAND_CODE(read_the_data_from_continuous_registers)
    PROPERTY(station_no, station, station(1))
    PROPERTY_ADDRESS(start_no)
    PROPERTY(addresses_count, int, 1)   // 1<=N<=256

public:
    virtual int dump(char* buffer, int size) const noexcept override;
};

/* ======================================================================= */
class the_status_reading_of_continuous_discrete final : public command
{
    COMMAND_CODE(the_status_reading_of_continuous_discrete)
    PROPERTY(station_no, station, station(1))
    PROPERTY_ADDRESS(start_no)
    PROPERTY(addresses_count, int, 1)   // 1<=N<=256

public:
    virtual int dump(char* buffer, int size) const noexcept override;
};


#undef PROPERTY_ADDRESS
#undef PROPERTY
#undef COMMAND_CODE

} /* namespace libfatek */
} /* namespace zcsevcik */
#endif  /* ZCSEVCIK_LIBFATEK_COMMAND_HPP_ */
