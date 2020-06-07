#ifndef _gg_app_window_info_base_h_
#define _gg_app_window_info_base_h_

// include files

#include "gg/core/string/type/string_ref.h"

// namespace

namespace gg::app
{
    // struct in charge of define a base window information

    struct window_info_base
    {
        string_ref m_name;

        uint16 m_width;
        uint16 m_height;
    };
}

#endif // _gg_app_window_info_base_h_
