#ifndef _gg_gfx_context_info_base_h_
#define _gg_gfx_context_info_base_h_

namespace gg::app { class window; }

namespace gg::gfx
{
    struct context_info_base
    {
        app::window const * m_window;
    };
}

#endif // _gg_gfx_context_info_base_h_
