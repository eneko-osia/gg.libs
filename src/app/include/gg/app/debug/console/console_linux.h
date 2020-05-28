#ifndef _gg_app_console_linux_h_
#define _gg_app_console_linux_h_

// include files

#include "gg/core/type/type.h"

// namespace

namespace gg::app
{
    // namespace in charge of define linux console

    namespace console
    {
        // methods

        inline void finalize(void) noexcept {}
        inline bool8 init(void) noexcept { return true; }
    }
}

#endif // _gg_app_console_linux_h_
