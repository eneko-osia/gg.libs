#ifndef _gg_application_linux_h_
#define _gg_application_linux_h_

// include files

#include "gg/app/application/window_application.h"

// namespace

namespace gg
{
    // forward declarations

    class string_ref;

    // type definitions

    typedef class application_linux application_platform;

    // class in charge of define a linux application

    class application_linux : public window_application
    {
    public:

        // methods

        window * create_window(
            uint32 id,
            string_ref const & name,
            uint16 width,
            uint16 height);
        void destroy_window(uint32 id);

    protected:

        // constructors

        application_linux(data const & data) noexcept;
        virtual ~application_linux(void) noexcept = default;

        // methods

        void handle_messages(void) noexcept;
    };
}

#endif // _gg_application_linux_h_
