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

    freopen("NUL:", "w", stderr);
    freopen("NUL:", "w", stdout);
    freopen("NUL:", "r", stdin);
    FreeConsole();
}

bool8 console::init(string_ref const & name) noexcept
{
    GG_RETURN_TRUE_IF_NOT_NULL(GetConsoleWindow());

    GG_RETURN_FALSE_IF_TRUE(FALSE == AllocConsole());
    GG_RETURN_FALSE_IF_TRUE(FALSE == SetConsoleTitle(name.c_str()));
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
