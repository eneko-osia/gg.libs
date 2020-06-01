
#ifndef _gg_gfx_context_h_
#define _gg_gfx_context_h_

// include files

#include "gg/core/type/type.h"

// forward declarations

namespace gg::app { class window; }

// namespace

namespace gg::gfx
{
    // class in charge of define an abstract graphics context

    class context
    {
    public:

        // constructors

        context(void) noexcept;
        virtual ~context(void) noexcept;

        // methods

        void finalize(void) noexcept;
        bool8 init(app::window const * window) noexcept;

    protected:

        // methods

        app::window const * get_window() const
        {
            return m_window;
        }

    private:

        // virtual methods

        virtual void on_finalize(void) noexcept = 0;
        virtual bool8 on_init(void) noexcept = 0;

    private:

        // attributes

        app::window const * m_window;
    };
}

#endif // _gg_gfx_context_h_
