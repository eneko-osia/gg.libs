#ifndef _gg_app_window_runtime_h_
#define _gg_app_window_runtime_h_

// include files

#include "gg/app/runtime/runtime_base.h"
#include "gg/core/container/array/array_dynamic.h"
#include "gg/core/container/container.h"

// namespace

namespace gg::app
{
    // forward declarations

    class window;

    // class in charge of define a window runtime

    class window_runtime : public runtime_base
    {
    public:

        // methods

        window * get_window(uint32 id) noexcept;
        window const * get_window(uint32 id) const noexcept;

    protected:

        // constructors

        window_runtime(data const & data) noexcept;
        virtual ~window_runtime(void) noexcept = default;

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

#endif // _gg_app_window_runtime_h_
