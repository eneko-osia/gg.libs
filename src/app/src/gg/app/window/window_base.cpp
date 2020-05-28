#include "gg/app/window/window.h"

//==============================================================================

#include "gg/core/string/type/string_ref.h"

//==============================================================================
namespace gg::app
{
//==============================================================================

window_base::window_base(id_type id, string_ref const & name) noexcept
    : identifiable<id_type>(id)
    , nameable<string_dynamic>(name)
    , sizeable<uint16>(0, 0)
{
}

//==============================================================================
}
//==============================================================================
