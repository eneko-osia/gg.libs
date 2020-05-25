#ifndef _gg_string_h_
#define _gg_string_h_

// include files

#include "gg/core/constant/constant.h"
#include "gg/core/debug/assert.h"
#include "gg/core/string/macro/macro.h"

// namespace

namespace gg
{
    // namespace in charge of define string utilities

    namespace string
    {
        // constants

        static constexpr size_type npos = uint32_max;

        // methods

        inline constexpr diff_type
        compare(char8 const * lhs, char8 const * rhs) noexcept
        {
            GG_ASSERT_NOT_NULL(lhs);
            GG_ASSERT_NOT_NULL(rhs);

            for (; (*lhs && *rhs) && (*lhs == *rhs); ++lhs, ++rhs) {}
            return *(uchar8 const *) lhs - *(uchar8 const *) rhs;
        }

        inline constexpr char8 const *
        find(char8 const * lhs, char8 const * rhs) noexcept
        {
            GG_ASSERT_NOT_NULL(lhs);
            GG_ASSERT_NOT_NULL(rhs);

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

        inline constexpr size_type length(char8 const * str) noexcept
        {
            GG_ASSERT_NOT_NULL(str);

            size_type size = 0;
            for (; *str; ++str, ++size) {}
            return size;
        }

        inline constexpr void trim(
            char8 * str,
            size_type size,
            char8 const * delims = GG_TEXT(" \t\r\n")) noexcept
        {
            GG_ASSERT_NOT_NULL(str);
            GG_ASSERT_NOT_NULL(delims);

            char8 const * str_end = str + size;
            char8 const * delims_end = delims + length(delims);
            for(char8 const * i = delims; i != delims_end; ++i)
            {
                size_type index = 0;
                for(char8 const * j = str; j != str_end; ++j)
                {
                    if (*i != *j)
                    {
                        str[index++] = (*j);
                    }
                }
                str[index] = '\0';
            }
        }
    }
}

#endif // _gg_string_h_
