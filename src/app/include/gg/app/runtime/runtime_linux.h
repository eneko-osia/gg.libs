#ifndef _gg_app_runtime_linux_h_
#define _gg_app_runtime_linux_h_

// include files

#include "gg/app/runtime/window_runtime.h"

// namespace

namespace gg::app
{
    // forward declarations

    class string_ref;

    // type definitions

    typedef class runtime_linux runtime_platform;

    // class in charge of define a linux runtime

    class runtime_linux : public window_runtime
    {
    public:

        // methods

        window * create_window(
            uint32 id,
            string_ref const & name,
            uint16 width,
            uint16 height);
        void destroy_window(uint32 id);

    protected:

        // constructors

        runtime_linux(data const & data) noexcept;
        virtual ~runtime_linux(void) noexcept = default;

        // methods

        void handle_messages(void) noexcept;
    };
}

#endif // _gg_app_runtime_linux_h_
