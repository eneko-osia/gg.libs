#include "gg/app/runtime/runtime_base.h"

//==============================================================================

#include "gg/app/window/window.h"

//==============================================================================
namespace gg::app
{
//==============================================================================

runtime_base::runtime_base(data const & data) noexcept
    : m_data(data)
{
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

void runtime_base::add_window(window * window) noexcept
{
    GG_ASSERT_NOT_NULL(window);
    GG_ASSERT_NULL(get_window(window->get_id()));
    m_windows.push_back(window);
}

window * runtime_base::get_window(uint32 id) noexcept
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

window const * runtime_base::get_window(uint32 id) const noexcept
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

void runtime_base::remove_window(uint32 id) noexcept
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
