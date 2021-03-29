//==============================================================================
#if defined(GG_APP_WINDOW_SUPPORT)
//==============================================================================

#include "gg/app/window/window_base.h"

//==============================================================================

#include "gg/app/window/window_info.h"
#include "gg/app/window/window.h"

//==============================================================================
namespace gg::app
{
//==============================================================================

void window_base::finalize(void) noexcept
{
    type::cast_static<window *>(this)->on_finalize();
}

bool8 window_base::init(window_info const & info) noexcept
{
    set_name(info.m_name);
    set_width(info.m_width);
    set_height(info.m_height);

    bool8 initialized = type::cast_static<window *>(this)->on_init(info);
    if (!initialized)
    {
        finalize();
    }
    return initialized;
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
