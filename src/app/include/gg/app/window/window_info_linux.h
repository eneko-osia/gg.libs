#ifndef _gg_app_window_info_linux_h_
#define _gg_app_window_info_linux_h_

// include files

#include "gg/app/window/window_info_base.h"

// namespace

namespace gg::app
{
    // type definitions

    typedef class window_info_linux window_info_platform;

    // struct in charge of define a linux window information

    struct window_info_linux : public window_info_base
    {
    };
}

#endif // _gg_app_window_info_linux_h_
