#ifndef _gg_app_window_base_h_
#define _gg_app_window_base_h_

// include files

#include "gg/app/window/iwindow_observer.h"
#include "gg/core/pattern/identifiable.h"
#include "gg/core/pattern/nameable.h"
#include "gg/core/pattern/observer/observable.h"
#include "gg/core/pattern/sizeable.h"
#include "gg/core/string/type/string_dynamic.h"

// namespace

namespace gg::app
{
    // class in charge of define a base window

    class window_base
        : public identifiable<id_type>
        , public nameable<string_dynamic>
        , public sizeable<uint16>
        , public observable<iwindow_observer>
    {
    protected:

        // constructors

        window_base(id_type id, string_ref const & name) noexcept;
        ~window_base(void) noexcept = default;
    };
}

#endif // _gg_app_window_base_h_
