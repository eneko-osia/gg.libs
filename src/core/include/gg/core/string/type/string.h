#ifndef _gg_string_h_
#define _gg_string_h_

// include files

#include "gg/core/constant/constant.h"
#include "gg/core/string/macro/macro.h"
#include "gg/core/type/type_trait.h"
#include <cstring>

// namespace

namespace gg
{
    // namespace in charge of define string utilities

    namespace string
    {
        // constants

        static constexpr size_type npos = uint32_max;

        // methods

        inline diff_type
        compare(char8 const * lstr, char8 const * rstr) noexcept
        {
            GG_ASSERT_NOT_NULL(lstr);
            GG_ASSERT_NOT_NULL(rstr);
            return std::strcmp(lstr, rstr);
        }

        inline char8 const *
        find(char8 const * lstr, char8 const * rstr) noexcept
        {
            GG_ASSERT_NOT_NULL(lstr);
            GG_ASSERT_NOT_NULL(rstr);
            return std::strstr(lstr, rstr);
        }

        inline size_type length(char8 const * str) noexcept
        {
            GG_ASSERT_NOT_NULL(str);
            return type::cast_static<size_type>(std::strlen(str));
        }

        inline void trim(
            char8 * str,
            size_type size,
            char8 const * delims = GG_TEXT(" \t\r\n")) noexcept
        {
            bool8 delim = false;
            size_type index = 0;

            char8 const * str_end = str + size;
            char8 const * delims_end = delims + length(delims);

            for(char8 const * i = str; i != str_end; ++i)
            {
                for(char8 const * j = delims; j != delims_end && !delim; ++j)
                {
                    if (*i == *j) { delim = true; }
                }

                if (!delim)
                {
                    str[index++] = (*i);
                }

                delim = false;
            }

            str[index] = '\0';
        }
    }
}

#endif // _gg_string_h_
