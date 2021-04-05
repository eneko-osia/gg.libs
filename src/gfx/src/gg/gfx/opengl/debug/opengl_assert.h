#ifndef _gg_gfx_opengl_assert_h_
#define _gg_gfx_opengl_assert_h_

#include "gg/core/debug/assert.h"

#if GG_ASSERT_ENABLED
#include "gg/gfx/opengl/opengl_includes.h"
#define GG_ASSERT_GL_ERROR() GG_ASSERT(GL_NO_ERROR == glGetError())
#else
#define GG_ASSERT_GL_ERROR()
#endif

#endif // _gg_gfx_opengl_assert_h_
