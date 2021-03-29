#ifndef _gg_app_data_windows_h_
#define _gg_app_data_windows_h_

#include "gg/app/data/data_base.h"
#include "gg/core/pattern/handle.h"

namespace gg::app
{
    class data_windows : public data_base
    {
    public:

        // accessors

        handle get_hinstance(void) const noexcept
        {
            return m_hinstance;
        }

        template <typename HANDLE_TYPE>
        HANDLE_TYPE get_hinstance(void) const noexcept
        {
            return m_hinstance.get<HANDLE_TYPE>();
        }

        void set_hinstance(handle hinstance) noexcept
        {
            m_hinstance = hinstance;
        }

        template <typename HANDLE_TYPE>
        void set_hinstance(HANDLE_TYPE hinstance) noexcept
        {
            m_hinstance.set(hinstance);
        }

    protected:

        // constructors

        data_windows(void) noexcept = default;
        ~data_windows(void) noexcept = default;

    private:

        // attributes

        handle m_hinstance;
    };

    typedef data_windows data_platform;
}

#endif // _gg_app_data_windows_h_
