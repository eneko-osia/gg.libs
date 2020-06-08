#ifndef _gg_app_runtime_windows_h_
#define _gg_app_runtime_windows_h_

#include "gg/app/runtime/runtime_base.h"

namespace gg { class string_ref; }

namespace gg::app
{
    class runtime_windows : public runtime_base
    {
    public:

        // methods

        id_type create_window(
            string_ref const & name,
            uint16 width,
            uint16 height) noexcept;

    protected:

        // constructors

        runtime_windows(data const & data) noexcept;
        virtual ~runtime_windows(void) noexcept= default;

        // methods

        void handle_messages(void) noexcept;
    };

    typedef runtime_windows runtime_platform;
}

#endif // _gg_app_runtime_windows_h_
