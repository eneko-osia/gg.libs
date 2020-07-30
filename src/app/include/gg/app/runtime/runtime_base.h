#ifndef _gg_app_runtime_base_h_
#define _gg_app_runtime_base_h_

#include "gg/core/pattern/singleton/singleton_manual.h"

#if defined(GG_APP_WINDOW_SUPPORT)
#include "gg/core/container/array/array_dynamic.h"
#include "gg/core/container/container.h"
#endif

namespace gg::app
{
    class data;
    class window;

    class runtime_base : public singleton_manual<runtime_base>
    {
    public:

        // static methods

        static int32 main(data const & data) noexcept;

        // accessors

        data const & get_data(void) const noexcept
        {
            return m_data;
        }

#if defined(GG_APP_WINDOW_SUPPORT)

        // methods

        void destroy_window(id_type id) noexcept;

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

        // accessors

        window * get_window(id_type id) noexcept;
        window const * get_window(id_type id) const noexcept;
#endif

    protected:

        // constructors

        runtime_base(data const & data) noexcept;
        virtual ~runtime_base(void) noexcept;

    private:

        // friendships

        friend class gg::memory;

        // static methods

        static void create(data const & data) noexcept;

        // virtual methods

        virtual int32 main(void) noexcept = 0;

    protected:

        // attributes

        data const & m_data;

#if defined(GG_APP_WINDOW_SUPPORT)

        // type definitions

        typedef array_dynamic<window> window_container;

        // attributes

        window_container m_windows;
#endif
    };
}

#ifdef GG_APPLICATION
    #undef GG_APPLICATION
#endif

#define GG_APPLICATION(RUNTIME_TYPE)                                \
    void gg::app::runtime_base::create(data const & data) noexcept  \
    {                                                               \
        singleton_manual<runtime_base>::create<RUNTIME_TYPE>(data); \
    }

#endif // _gg_app_runtime_base_h_
