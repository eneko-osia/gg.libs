#ifndef _gg_enum_h_
#define _gg_enum_h_

// include files

#include "gg/core/type/type.h"
#include <type_traits>

// undefined previous definitions

#ifdef GG_ENUM
    #undef GG_ENUM
#endif

// define enums

#define GG_ENUM(TYPE) \
    typedef gg::enums::underlying<TYPE>::type TYPE ## _underlying

// namespace

namespace gg
{
    // namespace in charge of define enumetarion utilities

    namespace enums
    {
        // structs

        template <typename TYPE>
        struct underlying
        {
            typedef typename std::underlying_type<TYPE>::type type;
        };

        // methods

        template <typename TYPE>
        constexpr typename underlying<TYPE>::type cast(TYPE value)
        {
            typedef typename underlying<TYPE>::type enum_value_type;
            return enum_value_type(value);
        }

        template <typename TYPE>
        constexpr TYPE cast(typename underlying<TYPE>::type value)
        {
            return TYPE(value);
        }
    }
}

template <typename TYPE>
constexpr TYPE operator&(TYPE left, TYPE right)
{
    return
        gg::enums::cast<TYPE>(
            gg::enums::cast(left) & gg::enums::cast(right));
}

template <typename TYPE>
constexpr TYPE operator|(TYPE left, TYPE right)
{
    return
        gg::enums::cast<TYPE>(
            gg::enums::cast(left) | gg::enums::cast(right));
}

template <typename TYPE>
constexpr TYPE operator^(TYPE left, TYPE right)
{
    return
        gg::enums::cast<TYPE>(
            gg::enums::cast(left) ^ gg::enums::cast(right));
}

template <typename TYPE>
constexpr TYPE operator~(TYPE value)
{
    return gg::enums::cast<TYPE>(~gg::enums::cast(value));
}

template <typename TYPE>
constexpr void operator&=(TYPE & left, TYPE right)
{
    left = left & right;
}

template <typename TYPE>
constexpr void operator|=(TYPE & left, TYPE right)
{
    left = left | right;
}

template <typename TYPE>
constexpr void operator^=(TYPE & left, TYPE right)
{
    left = left ^ right;
}

template <typename TYPE>
constexpr TYPE & operator++(TYPE & value)
{
    value = gg::enums::cast<TYPE>(gg::enums::cast(value) + 1);
    return value;
}

template <typename TYPE>
constexpr TYPE operator++(TYPE & value, int32)
{
    const TYPE result = value;
    ++value;
    return result;
}

#endif // _gg_enum_h_
