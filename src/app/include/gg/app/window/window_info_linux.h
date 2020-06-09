#ifndef _gg_app_window_info_linux_h_
#define _gg_app_window_info_linux_h_

#include "gg/app/window/window_info_base.h"

namespace gg::app
{
    struct window_info_linux : public window_info_base
    {
    };

    typedef window_info_linux window_info_platform;
}

#endif // _gg_app_window_info_linux_h_
