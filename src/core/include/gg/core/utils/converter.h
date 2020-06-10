#ifndef _gg_converter_h_
#define	_gg_converter_h_

#include "gg/core/type/type_trait.h"
#include "gg/core/utils/text_utils.h"
#include <cmath>

namespace gg
{
    namespace convert
    {
        // methods

        template <typename TYPE>
        TYPE to(char8 const * value) noexcept;

        template <>
        inline bool8 to<bool8>(char8 const * value) noexcept
        {
            return type::cast_static<bool8>(0 != ::atoi(value));
        }

        template <>
        inline int8 to<int8>(char8 const * value) noexcept
        {
            return type::cast_static<int8>(::atoi(value));
        }

        template <>
        inline int16 to<int16>(char8 const * value) noexcept
        {
            return type::cast_static<int16>(::atoi(value));
        }

        template <>
        inline int32 to<int32>(char8 const * value) noexcept
        {
            return type::cast_static<int32>(::atoi(value));
        }

        template <>
        inline int64 to<int64>(char8 const * value) noexcept
        {
            return type::cast_static<int64>(::atol(value));
        }

        template <>
        inline uint8 to<uint8>(char8 const * value) noexcept
        {
            return type::cast_static<uint8>(::atoi(value));
        }

        template <>
        inline uint16 to<uint16>(char8 const * value) noexcept
        {
            return type::cast_static<uint16>(::atoi(value));
        }

        template <>
        inline uint32 to<uint32>(char8 const * value) noexcept
        {
            return type::cast_static<uint32>(::atoi(value));
        }

        template <>
        inline uint64 to<uint64>(char8 const * value) noexcept
        {
            return type::cast_static<uint64>(::atol(value));
        }

        template <>
        inline float32 to<float32>(char8 const * value) noexcept
        {
            return type::cast_static<float32>(::atof(value));
        }

        template <>
        inline float64 to<float64>(char8 const * value) noexcept
        {
            return type::cast_static<float64>(::atof(value));
        }

        template <typename TYPE, typename FROM>
        TYPE to(FROM value) noexcept;

        template <>
        inline int32 to<int32, float32>(float32 value) noexcept
        {
            return
                type::cast_static<int32>(
                    value + ((fmodf(value, 1.0f) < 0.5f) ? 0 : 1));
        }

        template <>
        inline uint32 to<uint32, float32>(float32 value) noexcept
        {
            return
                type::cast_static<uint32>(
                    value + ((fmodf(value, 1.0f) < 0.5f) ? 0 : 1));
        }
    }

    namespace converter
    {
        // methods

        inline void btoa(bool8 b, char8 * buffer, uint32 size) noexcept
        {
            text_utils::format(buffer, size, "%d", b);
        }

        inline void ftoa(float32 f, char8 * buffer, uint32 size) noexcept
        {
            text_utils::format(buffer, size, "%f", f);
        }

        inline void itoa(int32 i, char8 * buffer, uint32 size) noexcept
        {
            text_utils::format(buffer, size, "%d", i);
        }

        inline float32 itof(int32 i) noexcept
        {
            return type::cast_static<float32>(i);
        }

        inline void ltoa(int64 l, char8 * buffer, uint32 size) noexcept
        {
            text_utils::format(buffer, size, "%lld", l);
        }

        inline void uitoa(uint32 u, char8 * buffer, uint32 size) noexcept
        {
            text_utils::format(buffer, size, "%u", u);
        }

        inline float32 uitof(uint32 u) noexcept
        {
            return type::cast_static<float32>(u);
        }
    }
}

#endif // _gg_converter_h_
