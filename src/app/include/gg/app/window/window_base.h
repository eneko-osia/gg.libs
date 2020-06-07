#ifndef _gg_app_window_base_h_
#define _gg_app_window_base_h_

// include files

#include "gg/app/window/iwindow_observer.h"
#include "gg/core/pattern/nameable.h"
#include "gg/core/pattern/observer/observable.h"
#include "gg/core/pattern/sizeable.h"
#include "gg/core/string/type/string_dynamic.h"

// forward declarations

namespace gg { class string_ref; }

// namespace

namespace gg::app
{
    // forward declarations

    struct window_info;

    // class in charge of define a base window

    class window_base
        : public nameable<string_dynamic>
        , public sizeable<uint16>
        , public observable<iwindow_observer>
    {
    public:

        // methods

        void finalize(void) noexcept;
        bool8 init(window_info const * info) noexcept;

    protected:

        // constructors

        window_base(void) noexcept = default;
        ~window_base(void) noexcept = default;

    private:

        // virtual methods

        virtual void on_finalize(void) noexcept = 0;
        virtual bool8 on_init(window_info const * info) noexcept = 0;
    };
}

#endif // _gg_app_window_base_h_
