#ifndef _gg_text_utils_h_
#define _gg_text_utils_h_

// include files

#include "gg/core/type/type_trait.h"
#include <cstdio>

// namespace

namespace gg
{
    // namespace in charge of define a text utilities

    namespace text_utils
    {
        // methods

        template <typename... ARGS>
        inline int32
        format(
            char8 * buffer,
            uint32 size,
            char8 const * message,
            ARGS &&... args)
        {
            return
                snprintf(buffer, size, message, type::forward<ARGS>(args)...);
        }
    };
}

#endif // _gg_text_utils_h_
