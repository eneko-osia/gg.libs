#ifndef _gg_app_window_linux_h_
#define _gg_app_window_linux_h_

#include "gg/app/window/window_base.h"
#include <X11/Xlib.h>

namespace gg::app
{
    class window_linux : public window_base
    {
    public:

        // methods

        void handle_messages(void) noexcept;

        // accessors

        Display * get_display(void) const noexcept
        {
            return m_display;
        }

        int32 get_screen(void) const noexcept
        {
            return m_screen;
        }

    protected:

        // constructors

        window_linux(void) noexcept;
        ~window_linux(void) noexcept;

    private:

        // friendships

        friend class window_base;

        // methods

        void on_finalize(void) noexcept;
        bool8 on_init(window_info const & info) noexcept;

        // attributes

        Display * m_display;
        int32 m_screen;
    };

    typedef window_linux window_platform;
}

#endif // _gg_app_window_linux_h_
