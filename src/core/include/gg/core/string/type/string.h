#ifndef _gg_string_h_
#define _gg_string_h_

#include "gg/core/debug/assert.h"
#include "gg/core/string/macro/macro.h"
#include "gg/core/type/constant.h"
#include "gg/core/type/type_trait.h"
#include <cstdio>

namespace gg
{
    namespace string
    {
        // constants

        static constexpr char8 const * empty = GG_TEXT("");
        static constexpr size_type npos = uint32_max;

        // methods

        inline constexpr diff_type
        compare(char8 const * lhs, char8 const * rhs) noexcept
        {
            GG_ASSERT(lhs);
            GG_ASSERT(rhs);

            for (; (*lhs && *rhs) && (*lhs == *rhs); ++lhs, ++rhs) {}
            return *(uchar8 const *) lhs - *(uchar8 const *) rhs;
        }

        inline constexpr char8 const *
        find(char8 const * lhs, char8 const * rhs) noexcept
        {
            GG_ASSERT(lhs);
            GG_ASSERT(rhs);

            for (; *lhs; ++lhs)
            {
                char8 const * j = rhs;
                for (char8 const * i = lhs; (*i && *j) && (*i == *j); ++i, ++j)
                {
                }

                if (!(*j))
                {
                    return lhs;
                }
            }
            return nullptr;
        }

        template <typename... ARGS>
        inline int32
        format(
            char8 * buffer,
            size_type size,
            char8 const * format,
            ARGS &&... args)
        {
            return
                snprintf(buffer, size, format, type::forward<ARGS>(args)...);
        }

        template <typename TYPE>
        void from(TYPE value, char8 * buffer, size_type size) noexcept;

        template <>
        inline void from<bool8>(bool8 value, char8 * buffer, size_type size) noexcept
        {
            format(buffer, size, "%d", value);
        }

        template <>
        inline void from<int32>(int32 value, char8 * buffer, size_type size) noexcept
        {
            format(buffer, size, "%d", value);
        }

        template <>
        inline void from<uint32>(uint32 value, char8 * buffer, size_type size) noexcept
        {
            format(buffer, size, "%u", value);
        }

        template <>
        inline void from<int64>(int64 value, char8 * buffer, size_type size) noexcept
        {
            format(buffer, size, "%lld", value);
        }

        template <>
        inline void from<float32>(float32 value, char8 * buffer, size_type size) noexcept
        {
            format(buffer, size, "%f", value);
        }

        inline constexpr size_type length(char8 const * str) noexcept
        {
            GG_ASSERT(str);

            size_type size = 0;
            for (; *str; ++str, ++size) {}
            return size;
        }

        inline constexpr size_type
        trim(
            char8 * str,
            size_type size,
            char8 const * delims = GG_TEXT(" \t\r\n")) noexcept
        {
            GG_ASSERT(str);
            GG_ASSERT(delims);

            char8 const * delims_end = delims + length(delims);
            for(char8 const * i = delims; i != delims_end; ++i)
            {
                size_type index = 0;
                char8 const * str_end = str + size;
                for(char8 const * j = str; j != str_end; ++j)
                {
                    if (*i != *j)
                    {
                        str[index++] = (*j);
                    }
                }
                str[index] = '\0';
                size = index;
            }

            return size;
        }
    }
}

#endif // _gg_string_h_
