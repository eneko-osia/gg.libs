#include "gg/app/runtime/runtime_base.h"

//==============================================================================

#include "gg/app/window/window.h"

//==============================================================================
namespace gg::app
{
//==============================================================================

runtime_base::runtime_base(data const & data) noexcept
    : m_data(data)
    , m_windows()
{
}

runtime_base::~runtime_base(void) noexcept
{
    for (id_type id = 0; id < id_type(m_windows.size()); ++id)
    {
        destroy_window(id);
    }
}

//==============================================================================

int32 runtime_base::main(data const & data) noexcept
{
    create(data);
    int32 result = get_instance().main();
    destroy();
    return result;
}

//==============================================================================

void runtime_base::destroy_window(id_type id) noexcept
{
    window * win = get_window(id);
    if (win)
    {
        win->finalize();
        m_windows.erase(id);
    }
}

window * runtime_base::get_window(id_type id) noexcept
{
    return (id < m_windows.size()) ? &m_windows[id] : nullptr;
}

window const * runtime_base::get_window(id_type id) const noexcept
{
    return (id < m_windows.size()) ? &m_windows[id] : nullptr;
}

//==============================================================================
}
//==============================================================================
