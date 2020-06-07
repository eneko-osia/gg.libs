#ifndef _gg_app_window_info_windows_h_
#define _gg_app_window_info_windows_h_

// include files

#include "gg/app/window/window_info_base.h"
#include <windows.h>

// namespace

namespace gg::app
{
    // type definitions

    typedef struct window_info_windows window_info_platform;

    // struct in charge of define a windows window information

    struct window_info_windows : public window_info_base
    {
        HINSTANCE m_hinstance;
    };
}

#endif // _gg_app_window_info_windows_h_
