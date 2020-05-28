#ifndef _gg_app_window_windows_h_
#define _gg_app_window_windows_h_

// include files

#include "gg/app/window/window_base.h"
#include <windows.h>

// namespace

namespace gg::app
{
    // type definitions

    typedef class window_windows window_platform;

    // class in charge of define a windows window

    class window_windows : public window_base
    {
    public:

        // methods

        void finalize(void) noexcept;
        bool8 init(uint16 width, uint16 height) noexcept;
        void handle_messages(UINT msg, WPARAM wparam, LPARAM lparam) noexcept;

        HWND get_hwnd(void) const noexcept
        {
            return m_hwnd;
        }

    protected:

        // constructors

        window_windows(id_type id, string_ref const & name) noexcept;
        ~window_windows(void) noexcept;

    private:

        // methods

        bool8 register_class(HINSTANCE hinstance) noexcept;
        bool8 unregister_class(void) noexcept;

        // attributes

        HWND m_hwnd;
        WNDCLASSEX m_wnd_class;
    };
}

#endif // _gg_app_window_windows_h_
