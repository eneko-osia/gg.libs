#ifndef _gg_app_window_h_
#define _gg_app_window_h_

// include files

#include "gg/app/window/window_platform.h"

// namespace

namespace gg::app
{
    // class in charge of define a window

    class window final : public window_platform
    {
    public:

        // constructors

        window(id_type id, string_ref const & name) noexcept;
        ~window(void) noexcept = default;
    };
}

#endif // _gg_app_window_h_
