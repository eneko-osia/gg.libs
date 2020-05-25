#ifndef _gg_app_data_windows_h_
#define _gg_app_data_windows_h_

// include files

#include "gg/app/data/data_base.h"
#include <wtypes.h>

// namespace

namespace gg::app
{
    // type definitions

    typedef class data_windows data_platform;

    // class in charge of define a windows application data

    class data_windows : public data_base
    {
    public:

        // methods

        HINSTANCE get_hinstance(void) const
        {
            return m_hinstance;
        }

        void set_hinstance(HINSTANCE hinstance)
        {
            m_hinstance = hinstance;
        }

    protected:

        // constructors

        data_windows(void)
            : m_hinstance(nullptr)
        {
        }

        ~data_windows(void) = default;

    private:

        // attributes

        HINSTANCE m_hinstance;
    };
}

#endif // _gg_app_data_windows_h_
