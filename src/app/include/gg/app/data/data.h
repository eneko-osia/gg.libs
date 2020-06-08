#ifndef _gg_app_data_h_
#define _gg_app_data_h_

#include "gg/app/data/data_platform.h"

namespace gg::app
{
    class data final : public data_platform
    {
    public:

        // constructors

        data(void) noexcept = default;
        ~data(void) noexcept = default;
    };
}

#endif // _gg_app_data_h_
