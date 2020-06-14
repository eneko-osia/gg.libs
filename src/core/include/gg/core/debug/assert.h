#ifndef _gg_assert_h_
#define _gg_assert_h_

// undefined previous definitions

#ifdef GG_ASSERT_ENABLED
    #undef GG_ASSERT_ENABLED
#endif

// define assert enabled

#if defined(GG_DEBUG)
    #define GG_ASSERT_ENABLED 1
#else
    #define GG_ASSERT_ENABLED 0
#endif

// include files

#include "gg/core/debug/assert_platform.h"

// undefined previous definitions

#ifdef GG_ASSERT
    #undef GG_ASSERT
#endif

#ifdef GG_ASSERT_FAILED
    #undef GG_ASSERT_FAILED
#endif

#ifdef GG_STATIC_ASSERT
    #undef GG_STATIC_ASSERT
#endif

// define asserts

#if GG_ASSERT_ENABLED

    #define GG_ASSERT(cond)                 GG_ASSERT_PLATFORM(cond)
    #define GG_ASSERT_FAILED()              GG_ASSERT(false)
    #define GG_STATIC_ASSERT(cond, message) static_assert(cond, message)

#else

    #define GG_ASSERT(cond)
    #define GG_ASSERT_FAILED()
    #define GG_STATIC_ASSERT(cond, message)

#endif

#endif // _gg_assert_h_
