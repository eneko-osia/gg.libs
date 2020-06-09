#include "gg/app/window/window.h"

//==============================================================================

#include "gg/app/window/window_info.h"

//==============================================================================
namespace gg::app
{
//==============================================================================

void window_base::finalize(void) noexcept
{
    on_finalize();
}

bool8 window_base::init(window_info const * info) noexcept
{
    GG_ASSERT_NOT_NULL(info);

    set_name(info->m_name);
    set_width(info->m_width);
    set_height(info->m_height);

    bool8 initialized = on_init(info);
    if (!initialized)
    {
        finalize();
    }
    return initialized;
}

//==============================================================================
}
//==============================================================================
