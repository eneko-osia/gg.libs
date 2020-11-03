#ifndef _gg_gfx_opengl_context_platform_h_
#define _gg_gfx_opengl_context_platform_h_

#if defined(GG_MAC)
    #error "Can't include opengl_context platform for mac osx"
#elif defined(GG_LINUX)
    #include "gg/gfx/opengl/context/opengl_context_linux.h"
#elif defined(GG_WINDOWS)
    #include "gg/gfx/opengl/context/opengl_context_windows.h"
#else
    #error "Can't include opengl context platform for unsupported platform"
#endif

#endif // _gg_gfx_opengl_context_platform_h_
