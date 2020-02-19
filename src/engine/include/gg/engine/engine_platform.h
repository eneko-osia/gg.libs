#ifndef _gg_engine_platform_h_
#define _gg_engine_platform_h_

// include files

#if defined(GG_MAC) || defined(GG_LINUX) || defined(GG_WINDOWS)
    #include "gg/engine/pc/engine_pc.h"
#else
    #error "Can't include engine platform for unsupported platform"
#endif

#endif // _gg_engine_platform_h_
