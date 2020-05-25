#ifndef _gg_app_window_platform_h_
#define _gg_app_window_platform_h_

// include files

#if defined(GG_MAC)
    #error "Can't include window platform for mac osx"
#elif defined(GG_LINUX)
    #include "gg/app/window/window_linux.h"
#elif defined(GG_WINDOWS)
    #include "gg/app/window/window_windows.h"
#else
    #error "Can't include window platform for unsupported platform"
#endif

#endif // _gg_app_window_platform_h_
