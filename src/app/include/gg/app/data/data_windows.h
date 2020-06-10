#ifndef _gg_app_data_windows_h_
#define _gg_app_data_windows_h_

#include "gg/app/data/data_base.h"
#include <windows.h>

namespace gg::app
{
    class data_windows : public data_base
    {
    public:

        // accessors

        HINSTANCE get_hinstance(void) const noexcept
        {
            return m_hinstance;
        }

        void set_hinstance(HINSTANCE hinstance) noexcept
        {
            m_hinstance = hinstance;
        }

    protected:

        // constructors

        data_windows(void) noexcept
            : m_hinstance(nullptr)
        {
        }
        ~data_windows(void) noexcept = default;

    private:

        // attributes

        HINSTANCE m_hinstance;
    };

    typedef data_windows data_platform;
}

#endif // _gg_app_data_windows_h_
