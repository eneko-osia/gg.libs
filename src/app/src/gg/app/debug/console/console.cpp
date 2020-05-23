#if defined(GG_WINDOWS)
//==============================================================================

#include "gg/app/debug/console/console.h"

//==============================================================================

#include "gg/app/application/application.h"
#include "gg/app/data/data.h"
#include <fcntl.h>
#include <fstream>
#include <io.h>
#include <iostream>
#include <stdio.h>
#include <windows.h>

//==============================================================================
namespace gg::console
{
//==============================================================================

static void handle_messages(uint32 fdw_ctrl_type)
{
    switch (fdw_ctrl_type)
    {
        case CTRL_CLOSE_EVENT:
        case CTRL_C_EVENT:
        {
            // application::get_instance().on_exit(nullptr);
            break;
        }

        default:
        {
            break;
        }
    }
}

//==============================================================================

void finalize(void) noexcept
{
}

bool8 init(void) noexcept
{
    // check if there is not already a console window

    GG_RETURN_TRUE_IF_TRUE_ASSERT(GetConsoleWindow());

    // allocate console

    GG_RETURN_FALSE_IF_FALSE_ASSERT(AllocConsole());

    // set console title

    SetConsoleTitle(application::get_instance().get_name().begin());

    // attach console

    AttachConsole(GetCurrentProcessId());

    // stdout handler

    GG_RETURN_FALSE_IF_FALSE_ASSERT(freopen("CONOUT$", "w", stdout));

    // set console handler

    GG_RETURN_FALSE_IF_FALSE_ASSERT(
        SetConsoleCtrlHandler((PHANDLER_ROUTINE) handle_messages, true));

    // sync with stdio

    std::ios::sync_with_stdio();

    return true;
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
