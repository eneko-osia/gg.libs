#ifndef _gg_app_data_platform_h_
#define _gg_app_data_platform_h_

// include files

#if defined(GG_MAC)
    #error "Can't include data platform for mac osx"
#elif defined(GG_LINUX)
    #include "gg/app/data/data_linux.h"
#elif defined(GG_WINDOWS)
    #include "gg/app/data/data_windows.h"
#else
    #error "Can't include data platform for unsupported platform"
#endif

#endif // _gg_app_data_platform_h_
