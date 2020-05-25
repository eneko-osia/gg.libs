#ifndef _gg_app_console_h_
#define _gg_app_console_h_

// include files

#include "gg/core/type/type.h"

// namespace

namespace gg::app
{
    // namespace in charge of define a console

    namespace console
    {
        // methods

        void finalize(void) noexcept;
        bool8 init(void) noexcept;
    }
}

#endif // _gg_app_console_h_
