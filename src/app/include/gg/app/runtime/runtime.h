#ifndef _gg_app_runtime_h_
#define _gg_app_runtime_h_

#include "gg/app/runtime/runtime_platform.h"

namespace gg::app
{
    class runtime : public runtime_platform
    {
    protected:

        // constructors

        runtime(data const & data) noexcept;
        virtual ~runtime(void) noexcept = default;
    };
}

#endif // _gg_app_runtime_h_
