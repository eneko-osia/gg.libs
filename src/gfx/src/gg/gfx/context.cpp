#include "gg/gfx/context.h"

//==============================================================================

#include "gg/core/macro/macro.h"
#include "gg/gfx/context_info.h"

//==============================================================================
namespace gg::gfx
{
//==============================================================================

context::context(void) noexcept
    : m_window(nullptr)
{
}

context::~context(void) noexcept
{
    finalize();
}

//==============================================================================

void context::finalize(void) noexcept
{
    GG_RETURN_IF_NULL(m_window);
    on_finalize();
    m_window = nullptr;
}

bool8
context::init(app::window const * window, context_info const * info) noexcept
{
    GG_RETURN_FALSE_IF_NOT_NULL(m_window);
    GG_ASSERT_NOT_NULL(window);
    GG_ASSERT_NOT_NULL(info);
    m_window = window;

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
