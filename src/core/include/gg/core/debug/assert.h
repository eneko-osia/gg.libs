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

#ifdef GG_ASSERT_FALSE
    #undef GG_ASSERT_FALSE
#endif

#ifdef GG_ASSERT_EQUALS
    #undef GG_ASSERT_EQUALS
#endif

#ifdef GG_ASSERT_NOT_EQUALS
    #undef GG_ASSERT_NOT_EQUALS
#endif

#ifdef GG_ASSERT_GREATER_THAN
    #undef GG_ASSERT_GREATER_THAN
#endif

#ifdef GG_ASSERT_GREATER_EQUAL_THAN
    #undef GG_ASSERT_GREATER_EQUAL_THAN
#endif

#ifdef GG_ASSERT_LESS_THAN
    #undef GG_ASSERT_LESS_THAN
#endif

#ifdef GG_ASSERT_LESS_EQUAL_THAN
    #undef GG_ASSERT_LESS_EQUAL_THAN
#endif

#ifdef GG_ASSERT_IN_RANGE
    #undef GG_ASSERT_IN_RANGE
#endif

#ifdef GG_ASSERT_NULL
    #undef GG_ASSERT_NULL
#endif

#ifdef GG_ASSERT_NOT_NULL
    #undef GG_ASSERT_NOT_NULL
#endif

#ifdef GG_ASSERT_SHOULDNT_BE_HERE
    #undef GG_ASSERT_SHOULDNT_BE_HERE
#endif

#ifdef GG_ASSERT_NOT_IMPLEMENTED
    #undef GG_ASSERT_NOT_IMPLEMENTED
#endif

#ifdef GG_STATIC_ASSERT
    #undef GG_STATIC_ASSERT
#endif

// define asserts

#if GG_ASSERT_ENABLED

    #define GG_ASSERT(cond)                                         \
        GG_ASSERT_PLATFORM(cond)

    #define GG_ASSERT_FAILED()                                      \
        GG_ASSERT(false)

    #define GG_ASSERT_FALSE(cond)                                   \
        GG_ASSERT(!(cond))

    #define GG_ASSERT_EQUALS(a, b)                                  \
        GG_ASSERT(((a) == (b)))

    #define GG_ASSERT_NOT_EQUALS(a, b)                              \
        GG_ASSERT(((a) != (b)))

    #define GG_ASSERT_GREATER_THAN(a, b)                            \
        GG_ASSERT(((a) > (b)))

    #define GG_ASSERT_GREATER_EQUAL_THAN(a, b)                      \
        GG_ASSERT(((a) >= (b)))

    #define GG_ASSERT_LESS_THAN(a, b)                               \
        GG_ASSERT(((a) < (b)))

    #define GG_ASSERT_LESS_EQUAL_THAN(a, b)                         \
        GG_ASSERT(((a) <= (b)))

    #define GG_ASSERT_IN_RANGE(a, min, max)                         \
        GG_ASSERT((((a) >= (min)) && ((a) <= (max))))

    #define GG_ASSERT_NULL(var)                                     \
        GG_ASSERT(nullptr == (var))

    #define GG_ASSERT_NOT_NULL(var)                                 \
        GG_ASSERT(nullptr != (var))

    #define GG_ASSERT_SHOULDNT_BE_HERE()                            \
        GG_ASSERT_FAILED()

    #define GG_ASSERT_NOT_IMPLEMENTED()                             \
        GG_ASSERT_FAILED()


#else

    #define GG_ASSERT(cond)
    #define GG_ASSERT_FAILED()
    #define GG_ASSERT_FALSE(cond)
    #define GG_ASSERT_EQUALS(a, b)
    #define GG_ASSERT_NOT_EQUALS(a, b)
    #define GG_ASSERT_GREATER_THAN(a, b)
    #define GG_ASSERT_LESS_THAN(a, b)
    #define GG_ASSERT_IN_RANGE(a, min, max)
    #define GG_ASSERT_NULL(var)
    #define GG_ASSERT_NOT_NULL(var)
    #define GG_ASSERT_SHOULDNT_BE_HERE()
    #define GG_ASSERT_NOT_IMPLEMENTED()

#endif

// define static assert

#define GG_STATIC_ASSERT(cond, message) static_assert(cond, message)

#endif // _gg_assert_h_
