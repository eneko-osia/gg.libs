#ifndef _gg_application_base_h_
#define _gg_application_base_h_

// include files

#include "gg/core/pattern/nameable.h"
#include "gg/core/pattern/singleton/singleton_manual.h"
#include "gg/core/string/type/string_dynamic.h"

// namespace

namespace gg
{
    // forward declarations

    class data;

    // class in charge of define a base application

    class application_base
        : public singleton_manual<application_base>
        , public nameable<string_dynamic>
    {
    public:

        // static methods

        static int32 main(data const & data) noexcept;

        // methods

        data const & get_data(void) const noexcept
        {
            return m_data;
        }

    protected:

        // constructors

        application_base(data const & data) noexcept;
        virtual ~application_base(void) noexcept = default;

    private:

        // friendships

        friend class memory;

        // static methods

        static void create(data const & data) noexcept;

        // virtual methods

        virtual int32 main(void) noexcept = 0;

    private:

        // attributes

        data const & m_data;
    };
}

// undefined previous definitions

#ifdef GG_APPLICATION
    #undef GG_APPLICATION
#endif

// define macros

#define GG_APPLICATION(APPLICATION_TYPE)                                    \
    void gg::application_base::create(data const & data) noexcept           \
    {                                                                       \
        singleton_manual<application_base>::create<APPLICATION_TYPE>(data); \
    }

#endif // _gg_app_application_base_h_
