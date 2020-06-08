#ifndef _gg_app_runtime_platform_h_
#define _gg_app_runtime_platform_h_

#if defined(GG_MAC)
    #error "Can't include runtime platform for mac osx"
#elif defined(GG_LINUX)
    #include "gg/app/runtime/runtime_linux.h"
#elif defined(GG_WINDOWS)
    #include "gg/app/runtime/runtime_windows.h"
#else
    #error "Can't include runtime platform for unsupported platform"
#endif

#endif // _gg_app_runtime_platform_h_
