#if defined(GG_WINDOWS)
//==============================================================================

#include "gg/app/debug/console/console_windows.h"

//==============================================================================

#include "gg/core/string/type/string_ref.h"
#include <cstdio>
#include <iostream>
#include <windows.h>

//==============================================================================
namespace gg::app
{
//==============================================================================

void console::finalize(void) noexcept
{
    GG_RETURN_IF_NULL(GetConsoleWindow());

    GG_RETURN_IF_NULL(freopen("NUL:", "w", stderr));
    GG_RETURN_IF_NULL(freopen("NUL:", "w", stdout));
    GG_RETURN_IF_NULL(freopen("NUL:", "r", stdin));
    GG_RETURN_IF_TRUE(FALSE == FreeConsole());
}

bool8 console::init(string_ref const & name) noexcept
{
    GG_RETURN_TRUE_IF_NOT_NULL(GetConsoleWindow());

    GG_RETURN_FALSE_IF_TRUE(FALSE == AllocConsole());
    GG_RETURN_FALSE_IF_TRUE(
        FALSE == SetConsoleTitle(name.begin()));
    GG_RETURN_FALSE_IF_NULL(freopen("CONIN$", "r", stdin));
    GG_RETURN_FALSE_IF_NULL(freopen("CONOUT$", "w", stdout));
    GG_RETURN_FALSE_IF_NULL(freopen("CONOUT$", "w", stderr));
    GG_RETURN_FALSE_IF_FALSE(std::ios::sync_with_stdio());
    return true;
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
