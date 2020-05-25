#ifndef _gg_app_runtime_h_
#define _gg_app_runtime_h_

// include files

#include "gg/app/runtime/runtime_platform.h"

// namespace

namespace gg::app
{
    // class in charge of define an runtime

    class runtime : public runtime_platform
    {
    protected:

        // constructors

        runtime(data const & data) noexcept;
        virtual ~runtime(void) noexcept = default;
    };
}

#endif // _gg_app_runtime_h_
