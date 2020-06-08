#ifndef _gg_app_runtime_linux_h_
#define _gg_app_runtime_linux_h_

#include "gg/app/runtime/runtime_base.h"

namespace gg { class string_ref; }

namespace gg::app
{
    class runtime_linux : public runtime_base
    {
    public:

        // methods

        id_type create_window(
            string_ref const & name,
            uint16 width,
            uint16 height) noexcept;

    protected:

        // constructors

        runtime_linux(data const & data) noexcept;
        virtual ~runtime_linux(void) noexcept = default;

        // methods

        void handle_messages(void) noexcept;
    };

    typedef runtime_linux runtime_platform;
}

#endif // _gg_app_runtime_linux_h_
