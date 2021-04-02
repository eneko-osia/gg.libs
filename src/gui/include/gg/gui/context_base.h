
#ifndef _gg_gui_context_base_h_
#define _gg_gui_context_base_h_

// include files

#include "gg/core/type/type.h"

// forward declarations

namespace gg::app { class window; }

// namespace

namespace gg::gui
{
    // class in charge of define an abstract gui context

    class context_base
    {
    public:

        // methods

        void finalize(void) noexcept;
        bool8 init(app::window const * window) noexcept;

    protected:

        // constructors

        context_base(void) noexcept;
        ~context_base(void) noexcept;

        // methods

        app::window const * get_window() const
        {
            return m_window;
        }

    private:

        // attributes

        app::window const * m_window;
    };
}

#endif // _gg_gui_context_base_h_
