#ifndef _gg_app_data_linux_h_
#define _gg_app_data_linux_h_

#include "gg/app/data/data_base.h"

namespace gg::app
{
    class data_linux : public data_base
    {
    protected:

        // constructors

        data_linux(void) noexcept = default;
        ~data_linux(void) noexcept = default;
    };

    typedef data_linux data_platform;
}

#endif // _gg_app_data_linux_h_
