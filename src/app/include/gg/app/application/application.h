#ifndef _gg_application_h_
#define _gg_application_h_

// include files

#include "gg/app/application/application_platform.h"

// namespace

namespace gg
{
    // class in charge of define an application

    class application : public application_platform
    {
    protected:

        // constructors

        application(data const & data) noexcept;
        virtual ~application(void) noexcept = default;
    };
}

#endif // _gg_application_h_
