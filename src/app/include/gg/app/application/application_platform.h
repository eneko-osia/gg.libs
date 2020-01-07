#ifndef _gg_application_platform_h_
#define _gg_application_platform_h_

// include files

#if defined(GG_MAC)
    #error "Can't include application platform for mac osx"
#elif defined(GG_LINUX)
    #include "gg/app/application/application_linux.h"
#elif defined(GG_WINDOWS)
    #include "gg/app/application/application_windows.h"
#else
    #error "Can't include application platform for unsupported platform"
#endif

#endif // _gg_application_platform_h_
