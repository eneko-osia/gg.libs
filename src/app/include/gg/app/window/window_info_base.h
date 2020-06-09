#ifndef _gg_app_window_info_base_h_
#define _gg_app_window_info_base_h_

#include "gg/core/string/type/string_ref.h"

namespace gg::app
{
    struct window_info_base
    {
        string_ref m_name;
        uint16 m_width;
        uint16 m_height;
    };
}

#endif // _gg_app_window_info_base_h_
