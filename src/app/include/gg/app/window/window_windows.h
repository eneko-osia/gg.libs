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

        void finalize(void);
        bool8 init(uint16 width, uint16 height);
        void handle_messages(UINT msg, WPARAM wparam, LPARAM lparam);

        HWND get_hwnd(void) const
        {
            return m_hwnd;
        }

    protected:

        // constructors

        window_windows(uint32 id, string_ref const & name);
        ~window_windows(void);

    private:

        // methods

        bool8 register_class(HINSTANCE hinstance);
        bool8 unregister_class(void);

        // attributes

        HWND m_hwnd;
        WNDCLASSEX m_wnd_class;
    };
}

#endif // _gg_app_window_windows_h_
