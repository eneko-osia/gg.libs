#ifndef _gg_app_console_windows_h_
#define _gg_app_console_windows_h_

// include files

#include "gg/core/type/type.h"

// forward declarations

namespace gg { class string_ref; }

// namespace

namespace gg::app
{
    // namespace in charge of define windows console

    namespace console
    {
        // methods

        void finalize(void) noexcept;
        bool8 init(string_ref const & name) noexcept;
    }
}

#endif // _gg_app_console_windows_h_
