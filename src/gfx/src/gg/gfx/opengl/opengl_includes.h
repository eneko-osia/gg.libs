#ifndef _gg_gfx_opengl_includes_h_
#define _gg_gfx_opengl_includes_h_

// include files

#include "GL/glew.h"

#if defined(GG_MAC)
    #error "Can't include glew for mac osx"
#elif defined(GG_LINUX)
    #include "GL/glxew.h"
#elif defined(GG_WINDOWS)
    #include "GL/wglew.h"
#else
    #error "Can't include glew for unsupported platform"
#endif

#endif // _gg_gfx_opengl_includes_h_
