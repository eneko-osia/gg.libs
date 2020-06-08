#ifndef _gg_app_console_platform_h_
#define _gg_app_console_platform_h_

#if defined(GG_MAC)
    #error "Can't include console platform for mac osx"
#elif defined(GG_LINUX)
    #include "gg/app/debug/console/console_linux.h"
#elif defined(GG_WINDOWS)
    #include "gg/app/debug/console/console_windows.h"
#else
    #error "Can't include console platform for unsupported platform"
#endif

#endif // _gg_app_console_platform_h_
