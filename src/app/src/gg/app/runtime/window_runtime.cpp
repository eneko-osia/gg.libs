#include "gg/app/runtime/window_runtime.h"

//==============================================================================

#include "gg/app/window/window.h"

//==============================================================================
namespace gg::app
{
//==============================================================================

window_runtime::window_runtime(data const & data) noexcept
    : runtime_base(data)
    , m_windows()
{
    static constexpr uint8 k_initial_allocation = 8;
    m_windows.reserve(k_initial_allocation);
}

//==============================================================================

void window_runtime::add_window(window * window)
{
    GG_ASSERT_NOT_NULL(window);
    GG_ASSERT_NULL(get_window(window->get_id()));

    m_windows.push_back(window);
}

window * window_runtime::get_window(uint32 id) noexcept
{
    auto it = container::find_if(
        m_windows.begin(),
        m_windows.end(),
        [&] (window_container::const_reference window)
        {
            return window->is_id(id);
        });
    return (it != m_windows.end()) ? *it : nullptr;
}

window const * window_runtime::get_window(uint32 id) const noexcept
{
    auto cit = container::find_if(
        m_windows.begin(),
        m_windows.end(),
        [&] (window_container::const_reference window)
        {
            return window->is_id(id);
        });
    return (cit != m_windows.end()) ? *cit : nullptr;
}

void window_runtime::remove_window(uint32 id)
{
    m_windows.erase(
        container::remove_if(
            m_windows.begin(),
            m_windows.end(),
            [&] (window_container::const_reference window)
            {
                return window->is_id(id);
            }));
}

//==============================================================================
}
//==============================================================================
