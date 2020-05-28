#ifndef _gg_app_data_linux_h_
#define _gg_app_data_linux_h_

// include files

#include "gg/app/data/data_base.h"

// namespace

namespace gg::app
{
    // type definitions

    typedef class data_linux data_platform;

    // class in charge of define a linux application data

    class data_linux : public data_base
    {
    protected:

        // constructors

        data_linux(void) = default;
        ~data_linux(void) = default;
    };
}

#endif // _gg_app_data_linux_h_
