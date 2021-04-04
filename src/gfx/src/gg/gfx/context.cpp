#include "gg/gfx/context.h"

//==============================================================================

#include "gg/core/debug/assert.h"
#include "gg/core/macro/macro.h"
#include "gg/gfx/context_info_base.h"

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
    GG_ASSERT(!m_window);
}

//==============================================================================

void context::finalize(void) noexcept
{
    GG_RETURN_IF(!m_window);
    on_finalize();
    m_window = nullptr;
}

bool8
context::init(app::window const * window, context_info_base const * info) noexcept
{
    GG_RETURN_FALSE_IF(m_window);
    GG_ASSERT(window);
    GG_ASSERT(info);
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
