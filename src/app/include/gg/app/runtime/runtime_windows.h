#ifndef _gg_app_runtime_windows_h_
#define _gg_app_runtime_windows_h_

// include files

#include "gg/app/runtime/window_runtime.h"

// forward declarations

namespace gg { class string_ref; }

// namespace

namespace gg::app
{
    // type definitions

    typedef class runtime_windows runtime_platform;

    // class in charge of define a windows runtime

    class runtime_windows : public window_runtime
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

        runtime_windows(data const & data) noexcept;
        virtual ~runtime_windows(void) noexcept= default;

        // methods

        void handle_messages(void) noexcept;
    };
}

#endif // _gg_app_runtime_windows_h_
