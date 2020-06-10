#ifndef _gg_app_runtime_base_h_
#define _gg_app_runtime_base_h_

#include "gg/core/container/array/array_dynamic.h"
#include "gg/core/container/container.h"
#include "gg/core/pattern/singleton/singleton_manual.h"

namespace gg::app
{
    class data;
    class window;

    class runtime_base : public singleton_manual<runtime_base>
    {
    public:

        // static methods

        static int32 main(data const & data) noexcept;

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

        data const & get_data(void) const noexcept
        {
            return m_data;
        }

        window * get_window(id_type id) noexcept;
        window const * get_window(id_type id) const noexcept;

    protected:

        // constructors

        runtime_base(data const & data) noexcept;
        virtual ~runtime_base(void) noexcept;

    private:

        // friendships

        friend class gg::memory;

        // type definitions

        typedef array_dynamic<window> window_container;

        // static methods

        static void create(data const & data) noexcept;

        // virtual methods

        virtual int32 main(void) noexcept = 0;

    protected:

        // attributes

        data const & m_data;
        window_container m_windows;
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
