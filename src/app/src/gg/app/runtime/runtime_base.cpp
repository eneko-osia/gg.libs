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
    for (auto * win : m_windows)
    {
        memory::delete_object(win);
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

void runtime_base::add_window(window * window) noexcept
{
    GG_ASSERT_NOT_NULL(window);
    m_windows.push_back(window);
}

window * runtime_base::create_window(
    id_type id,
    string_ref const & name,
    uint16 width, uint16 height) noexcept
{
    GG_ASSERT_NULL(get_window(id));
    window * win = memory::new_object<window>(id, name);
    if (win->init(width, height))
    {
        add_window(win);
    }
    else
    {
        memory::delete_object(win);
    }
    return win;
}

void runtime_base::destroy_window(uint32 id) noexcept
{
    window * win = get_window(id);
    if (win)
    {
        remove_window(id);
        win->finalize();
        memory::delete_object(win);
    }
}

window * runtime_base::get_window(id_type id) noexcept
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

window const * runtime_base::get_window(id_type id) const noexcept
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

void runtime_base::remove_window(id_type id) noexcept
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
