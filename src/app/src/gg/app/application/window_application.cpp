#include "gg/app/application/window_application.h"

//==============================================================================

#include "gg/app/window/window.h"

//==============================================================================
namespace gg
{
//==============================================================================

window_application::window_application(data const & data) noexcept
    : application_base(data)
    , m_windows()
{
    static constexpr uint8 k_initial_allocation = 8;
    m_windows.reserve(k_initial_allocation);
}

//==============================================================================

void window_application::add_window(window * window)
{
    GG_ASSERT_NOT_NULL(window);
    GG_ASSERT_NULL(get_window(window->get_id()));

    m_windows.push_back(window);
}

window * window_application::get_window(uint32 id) noexcept
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

window const * window_application::get_window(uint32 id) const noexcept
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

void window_application::remove_window(uint32 id)
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
