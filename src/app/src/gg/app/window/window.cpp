#include "gg/app/window/window.h"

//==============================================================================
namespace gg::app
{
//==============================================================================

window::window(id_type id, string_ref const & name) noexcept
    : window_platform(id, name)
{
}

//==============================================================================
}
//==============================================================================
