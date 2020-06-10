#ifndef _gg_converter_h_
#define	_gg_converter_h_

// include files

#include "gg/core/type/type_trait.h"
#include "gg/core/utils/text_utils.h"

#include <cmath>

// namespace

namespace gg
{
    namespace convert
    {
        // methods

        template <typename TYPE>
        TYPE to(char8 const * value) noexcept;

        template<>
        inline bool8 to<bool8>(char8 const * value) noexcept
        {
            return type::cast_static<bool8>(0 != ::atoi(value));
        }

        template<>
        inline int8 to<int8>(char8 const * value) noexcept
        {
            return type::cast_static<int8>(::atoi(value));
        }

        template<>
        inline float32 to<float32>(char8 const * value) noexcept
        {
            return type::cast_static<float32>(::atof(value));
        }

        template<>
        inline int32 to<int32>(char8 const * value) noexcept
        {
            return type::cast_static<int32>(::atoi(value));
        }

        template<>
        inline int64 to<int64>(char8 const * value) noexcept
        {
            return type::cast_static<int64>(::atol(value));
        }

        template<>
        inline int16 to<int16>(char8 const * value) noexcept
        {
            return type::cast_static<int16>(::atoi(value));
        }

        template<>
        inline uint8 to<uint8>(char8 const * value) noexcept
        {
            return type::cast_static<uint8>(::atoi(value));
        }

        template<>
        inline uint32 to<uint32>(char8 const * value) noexcept
        {
            return type::cast_static<uint32>(::atoi(value));
        }

        template<>
        inline uint64 to<uint64>(char8 const * value) noexcept
        {
            return type::cast_static<uint64>(::atol(value));
        }

        template<>
        inline uint16 to<uint16>(char8 const * value) noexcept
        {
            return type::cast_static<uint16>(::atoi(value));
        }
    }

    namespace converter
    {
        // methods

        inline bool8 atob(char8 const * value) noexcept
        {
            return type::cast_static<bool8>(0 != atoi(value));
        }

        inline int8 atoc(char8 const * value) noexcept
        {
            return type::cast_static<int8>(::atoi(value));
        }

        inline float32 atof(char8 const * value) noexcept
        {
            return type::cast_static<float32>(::atof(value));
        }

        inline int32 atoi(char8 const * value) noexcept
        {
            return type::cast_static<int32>(::atoi(value));
        }

        inline int64 atol(char8 const * value) noexcept
        {
            return type::cast_static<int64>(::atol(value));
        }

        inline int16 atos(char8 const * value) noexcept
        {
            return type::cast_static<int16>(atoi(value));
        }

        inline uint8 atouc(char8 const * value) noexcept
        {
            return type::cast_static<uint8>(::atoi(value));
        }

        inline uint32 atoui(char8 const * value) noexcept
        {
            return type::cast_static<uint32>(::atoi(value));
        }

        inline uint64 atoul(char8 const * value) noexcept
        {
            return type::cast_static<uint64>(::atol(value));
        }

        inline uint16 atous(char8 const * value) noexcept
        {
            return type::cast_static<uint16>(atoui(value));
        }

        inline void btoa(bool8 b, char8 * buffer, uint32 size) noexcept
        {
            text_utils::format(buffer, size, "%d", b);
        }

        inline void ftoa(float32 f, char8 * buffer, uint32 size) noexcept
        {
            text_utils::format(buffer, size, "%f", f);
        }

        inline int32 ftoi(float32 f) noexcept
        {
            return type::cast_static<int32>(f + ((fmodf(f, 1.0f) < 0.5f) ? 0 : 1));
        }

        inline uint32 ftou(float32 f) noexcept
        {
            return type::cast_static<uint32>(f + ((fmodf(f, 1.0f) < 0.5f) ? 0 : 1));
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
