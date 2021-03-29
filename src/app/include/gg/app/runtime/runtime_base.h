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

    #if defined(GG_APP_WINDOW_SUPPORT)
    class window;
    #endif

    class runtime_base : public singleton_manual<runtime_base>
    {
    public:

        // static methods

        static int32 main(data const & data) noexcept;

        // methods

        #if defined(GG_APP_WINDOW_SUPPORT)
        void destroy_window(id_type id) noexcept;
        #endif

        #if defined(GG_APP_WINDOW_SUPPORT)
        template <typename FUNCTION>
        void for_each_window(FUNCTION && function) noexcept
        {
            container::for_each(
                m_windows.begin(),
                m_windows.end(),
                type::forward<FUNCTION>(function));
        }
        #endif

        #if defined(GG_APP_WINDOW_SUPPORT)
        template <typename FUNCTION>
        void for_each_window(FUNCTION && function) const noexcept
        {
            container::for_each(
                m_windows.begin(),
                m_windows.end(),
                type::forward<FUNCTION>(function));
        }
        #endif

        // accessors

        data const & get_data(void) const noexcept
        {
            return m_data;
        }

        #if defined(GG_APP_WINDOW_SUPPORT)
        window * get_window(id_type id) noexcept;
        #endif

        #if defined(GG_APP_WINDOW_SUPPORT)
        window const * get_window(id_type id) const noexcept;
        #endif

    protected:

        // type definitions

        #if defined(GG_APP_WINDOW_SUPPORT)
        typedef array_dynamic<window> window_container;
        #endif

        // constructors

        runtime_base(data const & data) noexcept;
        virtual ~runtime_base(void) noexcept;

        // attributes

        #if defined(GG_APP_WINDOW_SUPPORT)
        window_container m_windows;
        #endif

    private:

        // friendships

        friend class gg::memory;

        // static methods

        static void create(data const & data) noexcept;

        // virtual methods

        virtual int32 main(void) noexcept = 0;

        // attributes

        data const & m_data;
    };
}

#define GG_APPLICATION(RUNTIME_TYPE)                                \
    void gg::app::runtime_base::create(data const & data) noexcept  \
    {                                                               \
        singleton_manual<runtime_base>::create<RUNTIME_TYPE>(data); \
    }

#endif // _gg_app_runtime_base_h_
