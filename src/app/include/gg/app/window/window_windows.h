#ifndef _gg_app_window_windows_h_
#define _gg_app_window_windows_h_

#include "gg/app/window/window_base.h"
#include <windows.h>

namespace gg::app
{
    class window_windows : public window_base
    {
    public:

        // methods

        bool8 handle_messages(UINT msg, WPARAM wparam, LPARAM lparam) noexcept;

        HWND get_hwnd(void) const noexcept
        {
            return m_hwnd;
        }

    protected:

        // constructors

        window_windows(void) noexcept;
        virtual ~window_windows(void) noexcept;

    private:

        // window_base override methods

        void on_finalize(void) noexcept override final;
        bool8 on_init(window_info const * info) noexcept override final;

        // methods

        bool8 register_class(HINSTANCE hinstance) noexcept;
        bool8 unregister_class(void) noexcept;

    private:

        // attributes

        HWND m_hwnd;
        WNDCLASSEX m_wnd_class;
    };

    typedef window_windows window_platform;
}

#endif // _gg_app_window_windows_h_
