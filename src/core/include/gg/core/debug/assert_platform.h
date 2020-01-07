#ifndef _gg_assert_platform_h_
#define _gg_assert_platform_h_

// undefined previous definitions

#ifdef GG_ASSERT_PLATFORM
    #undef GG_ASSERT_PLATFORM
#endif

// define asserts

#if GG_ASSERT_ENABLED

    #if defined(GG_MSVC)
        #define GG_DEBUG_BREAK __debugbreak()
    #else
        #define GG_DEBUG_BREAK
    #endif

    // include files

    #include <cassert>

    // define

    #define GG_ASSERT_PLATFORM(cond)    \
        if (!(cond))                    \
        {                               \
            GG_DEBUG_BREAK;             \
            assert(cond);               \
        }
#endif

#endif // _gg_assert_platform_h_
