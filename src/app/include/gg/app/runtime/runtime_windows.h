#ifndef _gg_app_runtime_windows_h_
#define _gg_app_runtime_windows_h_

// include files

#include "gg/app/runtime/runtime_base.h"

// forward declarations

namespace gg { class string_ref; }

// namespace

namespace gg::app
{
    // type definitions

    typedef class runtime_windows runtime_platform;

    // class in charge of define a windows runtime

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
}

#endif // _gg_app_runtime_windows_h_
