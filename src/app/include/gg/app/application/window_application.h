#ifndef _gg_window_application_h_
#define _gg_window_application_h_

// include files

#include "gg/app/application/application_base.h"
#include "gg/core/container/array/array_dynamic.h"
#include "gg/core/container/container.h"

// namespace

namespace gg
{
    // forward declarations

    class window;

    // class in charge of define a window application

    class window_application : public application_base
    {
    public:

        // methods

        window * get_window(uint32 id) noexcept;
        window const * get_window(uint32 id) const noexcept;

    protected:

        // constructors

        window_application(data const & data) noexcept;
        virtual ~window_application(void) noexcept = default;

        // methods

        void add_window(window * window);
        void remove_window(uint32 id);

        template <typename FUNCTION>
        void for_each_window(FUNCTION && function) noexcept
        {
            container::for_each(
                m_windows.begin(),
                m_windows.end(),
                type::forward<FUNCTION>(function));
        }

        template <typename FUNCTION>
        void for_each_window(FUNCTION && function) const noexcept
        {
            container::for_each(
                m_windows.begin(),
                m_windows.end(),
                type::forward<FUNCTION>(function));
        }

    private:

        // type definitions

        typedef array_dynamic<window*> window_container;

    private:

        // attributes

        window_container m_windows;
    };
}

#endif // _gg_app_window_application_h_
