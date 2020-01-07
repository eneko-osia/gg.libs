#ifndef _gg_window_base_h_
#define _gg_window_base_h_

// include files

#include "gg/app/window/iwindow_observer.h"
#include "gg/core/pattern/observer/observable.h"

#include "gg/core/pattern/identifiable.h"
#include "gg/core/pattern/nameable.h"
#include "gg/core/pattern/sizeable.h"
#include "gg/core/string/type/string_dynamic.h"
#include "gg/core/string/type/string_ref.h"

// namespace

namespace gg
{
    // class in charge of define a base window

    class window_base
        : public identifiable<uint32>
        , public nameable<string_dynamic>
        , public sizeable<uint16>
        , public observable<iwindow_observer>
    {
    protected:

        // constructors

        window_base(uint32 id, string_ref const & name)
            : identifiable<uint32>(id)
            , nameable<string_dynamic>(type::move(string_dynamic(name)))
            , sizeable<uint16>(0, 0)
        {
        }

        ~window_base(void) = default;
    };
}

#endif // _gg_window_base_h_
