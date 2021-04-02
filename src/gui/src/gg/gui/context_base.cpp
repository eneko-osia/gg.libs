#include "gg/gui/context_base.h"

//==============================================================================

#include "gg/core/debug/assert.h"
#include "gg/core/macro/macro.h"

//==============================================================================
namespace gg::gui
{
//==============================================================================

context_base::context_base(void) noexcept
    : m_window(nullptr)
{
}

context_base::~context_base(void) noexcept
{
    GG_ASSERT(!m_window);
}

//==============================================================================

void context_base::finalize(void) noexcept
{
    GG_RETURN_IF(!m_window);
    // on_finalize();
    m_window = nullptr;
}

bool8
context_base::init(app::window const * window) noexcept
{
    GG_RETURN_FALSE_IF(m_window);
    GG_ASSERT(window);
    m_window = window;

    // bool8 initialized = on_init(info);
    // if (!initialized)
    // {
    //     finalize();
    // }
    // return initialized;
    return true;
}

//==============================================================================
}
//==============================================================================
