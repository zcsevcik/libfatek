/*
 * zcsevcik/libfatek/detail/symbol.hpp.re
 *
 * Author(s):      Radek Sevcik <zcsevcik@gmail.com>
 * Date:           2017/05/28
 *
 * This file is part of zcsevcik/libfatek.
 */

#ifndef ZCSEVCIK_LIBFATEK_DETAIL_SYMBOL_HPP_
#define ZCSEVCIK_LIBFATEK_DETAIL_SYMBOL_HPP_

namespace zcsevcik {
namespace libfatek {
namespace detail {

class symbol final
{
public:
    enum value_type {
        X, WX, DWX,
        Y, WY, DWY,
        M, WM, DWM,
        S, WS, DWS,
        T, WT, DWT,
        C, WC, DWC,
           RT, DRT,
           RC, DRC,
            R,  DR,
            D,  DD,
            F,  DF,
    };

public:
    constexpr explicit symbol(value_type v) noexcept
      : value(v)
    {
    }

    static symbol from_string(const char*) noexcept;

public:
    const char* to_string() const noexcept;

    explicit operator bool() const noexcept
    {
        return value != (value_type)-1;
    }

    operator value_type() const noexcept
    {
        return value;
    }

private:
    value_type value;
};

symbol symbol::from_string(const char* YYCURSOR) noexcept
{
  /*!re2c
    re2c:define:YYCTYPE = char;
    re2c:yyfill:enable = 0;

    dec = [0-9]+;
    end = "\x00";

    "*"           { return symbol{(symbol::value_type)-1}; }
    "C"   dec end { return symbol{C}; }
    "WC"  dec end { return symbol{WC}; }
    "DWC" dec end { return symbol{DWC}; }
    "RC"  dec end { return symbol{RC}; }
    "DRC" dec end { return symbol{DRC}; }
    "D"   dec end { return symbol{D}; }
    "DD"  dec end { return symbol{DD}; }
    "R"   dec end { return symbol{R}; }
    "DR"  dec end { return symbol{DR}; }
    "F"   dec end { return symbol{F}; }
    "DF"  dec end { return symbol{DF}; }
    "X"   dec end { return symbol{X}; }
    "WX"  dec end { return symbol{WX}; }
    "DWX" dec end { return symbol{DWX}; }
    "M"   dec end { return symbol{M}; }
    "WM"  dec end { return symbol{WM}; }
    "DWM" dec end { return symbol{DWM}; }
    "Y"   dec end { return symbol{Y}; }
    "WY"  dec end { return symbol{WY}; }
    "DWY" dec end { return symbol{DWY}; }
    "S"   dec end { return symbol{S}; }
    "WS"  dec end { return symbol{WS}; }
    "DWS" dec end { return symbol{DWS}; }
    "T"   dec end { return symbol{T}; }
    "WT"  dec end { return symbol{WT}; }
    "DWT" dec end { return symbol{DWT}; }
    "RT"  dec end { return symbol{RT}; }
    "DRT" dec end { return symbol{DRT}; }
  */
}

const char* symbol::to_string() const noexcept
{
    switch(value)
    {
    default:    return "";
    case X:     return "X";
    case WX:    return "WX";
    case DWX:   return "DWX";
    case Y:     return "Y";
    case WY:    return "WY";
    case DWY:   return "DWY";
    case M:     return "M";
    case WM:    return "WM";
    case DWM:   return "DWM";
    case S:     return "S";
    case WS:    return "WS";
    case DWS:   return "DWS";
    case T:     return "T";
    case WT:    return "WT";
    case DWT:   return "DWT";
    case C:     return "C";
    case WC:    return "WC";
    case DWC:   return "DWC";
    case RT:    return "RT";
    case DRT:   return "DRT";
    case RC:    return "RC";
    case DRC:   return "DRC";
    case R:     return "R";
    case DR:    return "DR";
    case D:     return "D";
    case DD:    return "DD";
    case F:     return "F";
    case DF:    return "DF";
    }
}

} /* namespace detail */
} /* namespace libfatek */
} /* namespace zcsevcik */

#endif /* ZCSEVCIK_LIBFATEK_DETAIL_SYMBOL_HPP_ */
