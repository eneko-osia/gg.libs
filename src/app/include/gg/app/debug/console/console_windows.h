#ifndef _gg_app_console_windows_h_
#define _gg_app_console_windows_h_

#include "gg/core/type/type.h"

namespace gg { class string_ref; }

namespace gg::app
{
    namespace console
    {
        // methods

        void finalize(void) noexcept;
        bool8 init(string_ref const & name) noexcept;
    }
}

#endif // _gg_app_console_windows_h_
