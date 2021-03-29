//==============================================================================
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
    GG_RETURN_IF(!GetConsoleWindow());
    freopen("NUL:", "w", stderr);
    freopen("NUL:", "w", stdout);
    freopen("NUL:", "r", stdin);
    FreeConsole();
}

bool8 console::init(string_ref const & name) noexcept
{
    GG_RETURN_TRUE_IF(GetConsoleWindow());
    GG_RETURN_FALSE_IF(FALSE == AllocConsole());
    GG_RETURN_FALSE_IF(FALSE == SetConsoleTitle(name.c_str()));
    GG_RETURN_FALSE_IF(!freopen("CONIN$", "r", stdin));
    GG_RETURN_FALSE_IF(!freopen("CONOUT$", "w", stdout));
    GG_RETURN_FALSE_IF(!freopen("CONOUT$", "w", stderr));
    GG_RETURN_FALSE_IF(!std::ios::sync_with_stdio());
    return true;
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
