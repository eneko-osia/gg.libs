#ifndef _gg_app_window_info_windows_h_
#define _gg_app_window_info_windows_h_

#include "gg/app/window/window_info_base.h"
#include <windows.h>

namespace gg::app
{
    struct window_info_windows : public window_info_base
    {
        HINSTANCE m_hinstance;
    };

    typedef struct window_info_windows window_info_platform;
}

#endif // _gg_app_window_info_windows_h_
