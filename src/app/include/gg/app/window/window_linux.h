#ifndef _gg_app_window_linux_h_
#define _gg_app_window_linux_h_

// include files

#include "gg/app/window/window_base.h"
#include <X11/Xlib.h>

// namespace

namespace gg::app
{
    // type definitions

    typedef class window_linux window_platform;

    // class in charge of define a linux window

    class window_linux : public window_base
    {
    public:

        // methods

        void handle_messages(void) noexcept;

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

        // window_base override methods

        void on_finalize(void) noexcept override final;
        bool8 on_init(window_info const * info) noexcept override final;

    private:

        // attributes

        Display * m_display;
        int32 m_screen;
    };
}

#endif // _gg_app_window_linux_h_
