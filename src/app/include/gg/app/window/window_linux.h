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

        bool8 init(uint16 width, uint16 height);
        void finalize(void);
        void handle_messages(void);

        Display * get_display(void) const
        {
            return m_display;
        }

        int32 get_screen(void) const
        {
            return m_screen;
        }

    protected:

        // constructors

        window_linux(uint32 id, string_ref const & name);
        ~window_linux(void);

    private:

        // attributes

        Display * m_display;
        int32 m_screen;
    };
}

#endif // _gg_app_window_linux_h_
