#ifndef _gg_app_window_windows_h_
#define _gg_app_window_windows_h_

#include "gg/app/window/window_base.h"
#include "gg/core/pattern/handle.h"

namespace gg::app
{
    class window_windows : public window_base
    {
    public:

        // methods

        bool8 handle_messages(uint32 msg, int64 wparam, int64 lparam) noexcept;

        // accessors

        template <typename HANDLE_TYPE>
        HANDLE_TYPE get_hwnd(void) const noexcept
        {
            return m_hwnd.get<HANDLE_TYPE>();
        }

    protected:

        // constructors

        window_windows(void) noexcept;
        ~window_windows(void) noexcept;

    private:

        // window_base override methods

        void on_finalize(void) noexcept override final;
        bool8 on_init(window_info const & info) noexcept override final;

        // methods

        bool8 register_class(window_info const & info) noexcept;
        bool8 unregister_class(void) noexcept;

    private:

        // attributes

        handle m_hwnd;
        handle m_wnd_class;
    };

    typedef window_windows window_platform;
}

#endif // _gg_app_window_windows_h_
