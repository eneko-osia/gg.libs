#ifndef _gg_gfx_opengl_context_info_h_
#define _gg_gfx_opengl_context_info_h_

#include "gg/core/type/type.h"
#include "gg/gfx/context_info_base.h"

namespace gg::gfx
{
    struct opengl_context_info : public context_info_base
    {
        uint8 m_red_size;
        uint8 m_green_size;
        uint8 m_blue_size;
        uint8 m_alpha_size;

        uint8 m_depth_size;
        uint8 m_stencil_size;

        bool8 m_full_screen;
        bool8 m_vsync_enabled;

        uint8 m_version_major;
        uint8 m_version_minor;
    };
}

#endif // _gg_gfx_opengl_context_info_h_
