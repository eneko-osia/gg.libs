#ifndef _gg_app_window_info_windows_h_
#define _gg_app_window_info_windows_h_

#include "gg/app/window/window_info_base.h"
#include "gg/core/pattern/handle.h"

namespace gg::app
{
    struct window_info_windows : public window_info_base
    {
        handle m_hinstance;
    };

    typedef struct window_info_windows window_info_platform;
}

#endif // _gg_app_window_info_windows_h_
