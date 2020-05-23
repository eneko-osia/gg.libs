#ifndef _gg_console_h_
#define _gg_console_h_

// include files

#include "gg/core/type/type.h"

// namespace

namespace gg
{
    // namespace in charge of define a console

    namespace console
    {
        // methods

        void finalize(void) noexcept;
        bool8 init(void) noexcept;
    }
}

#endif // _gg_console_h_
