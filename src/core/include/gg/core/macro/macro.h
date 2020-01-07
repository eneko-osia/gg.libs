#ifndef _gg_macro_h_
#define _gg_macro_h_

// include files

#include "gg/core/debug/assert.h"

// undefined previous definitions

#ifdef GG_DO_IF_FALSE
    #undef GG_DO_IF_FALSE
#endif

#ifdef GG_DO_IF_FALSE_ASSERT
    #undef GG_DO_IF_FALSE_ASSERT
#endif

#ifdef GG_DO_IF_NOT_NULL
    #undef GG_DO_IF_NOT_NULL
#endif

#ifdef GG_DO_IF_NOT_NULL_ASSERT
    #undef GG_DO_IF_NOT_NULL_ASSERT
#endif

#ifdef GG_DO_IF_NULL
    #undef GG_DO_IF_NULL
#endif

#ifdef GG_DO_IF_NULL_ASSERT
    #undef GG_DO_IF_NULL_ASSERT
#endif

#ifdef GG_DO_IF_TRUE
    #undef GG_DO_IF_TRUE
#endif

#ifdef GG_DO_IF_TRUE_ASSERT
    #undef GG_DO_IF_TRUE_ASSERT
#endif

#ifdef GG_CONTINUE_IF_FALSE
    #undef GG_CONTINUE_IF_FALSE
#endif

#ifdef GG_CONTINUE_IF_FALSE_ASSERT
    #undef GG_CONTINUE_IF_FALSE_ASSERT
#endif

#ifdef GG_CONTINUE_IF_NOT_NULL
    #undef GG_CONTINUE_IF_NOT_NULL
#endif

#ifdef GG_CONTINUE_IF_NOT_NULL_ASSERT
    #undef GG_CONTINUE_IF_NOT_NULL_ASSERT
#endif

#ifdef GG_CONTINUE_IF_NULL
    #undef GG_CONTINUE_IF_NULL
#endif

#ifdef GG_CONTINUE_IF_NULL_ASSERT
    #undef GG_CONTINUE_IF_NULL_ASSERT
#endif

#ifdef GG_CONTINUE_IF_TRUE
    #undef GG_CONTINUE_IF_TRUE
#endif

#ifdef GG_CONTINUE_IF_TRUE_ASSERT
    #undef GG_CONTINUE_IF_TRUE_ASSERT
#endif

#ifdef GG_RETURN_FALSE_IF_FALSE
    #undef GG_RETURN_FALSE_IF_FALSE
#endif

#ifdef GG_RETURN_FALSE_IF_FALSE_ASSERT
    #undef GG_RETURN_FALSE_IF_FALSE_ASSERT
#endif

#ifdef GG_RETURN_FALSE_IF_NOT_NULL
    #undef GG_RETURN_FALSE_IF_NOT_NULL
#endif

#ifdef GG_RETURN_FALSE_IF_NOT_NULL_ASSERT
    #undef GG_RETURN_FALSE_IF_NOT_NULL_ASSERT
#endif

#ifdef GG_RETURN_FALSE_IF_NULL
    #undef GG_RETURN_FALSE_IF_NULL
#endif

#ifdef GG_RETURN_FALSE_IF_NULL_ASSERT
    #undef GG_RETURN_FALSE_IF_NULL_ASSERT
#endif

#ifdef GG_RETURN_FALSE_IF_TRUE
    #undef GG_RETURN_FALSE_IF_TRUE
#endif

#ifdef GG_RETURN_FALSE_IF_TRUE_ASSERT
    #undef GG_RETURN_FALSE_IF_TRUE_ASSERT
#endif

#ifdef GG_RETURN_IF_FALSE
    #undef GG_RETURN_IF_FALSE
#endif

#ifdef GG_RETURN_IF_FALSE_ASSERT
    #undef GG_RETURN_IF_FALSE_ASSERT
#endif

#ifdef GG_RETURN_IF_NOT_NULL
    #undef GG_RETURN_IF_NOT_NULL
#endif

#ifdef GG_RETURN_IF_NOT_NULL_ASSERT
    #undef GG_RETURN_IF_NOT_NULL_ASSERT
#endif

#ifdef GG_RETURN_IF_NULL
    #undef GG_RETURN_IF_NULL
#endif

#ifdef GG_RETURN_IF_NULL_ASSERT
    #undef GG_RETURN_IF_NULL_ASSERT
#endif

#ifdef GG_RETURN_IF_TRUE
    #undef GG_RETURN_IF_TRUE
#endif

#ifdef GG_RETURN_IF_TRUE_ASSERT
    #undef GG_RETURN_IF_TRUE_ASSERT
#endif

#ifdef GG_RETURN_NULL_IF_FALSE
    #undef GG_RETURN_NULL_IF_FALSE
#endif

#ifdef GG_RETURN_NULL_IF_FALSE_ASSERT
    #undef GG_RETURN_NULL_IF_FALSE_ASSERT
#endif

#ifdef GG_RETURN_NULL_IF_NOT_NULL
    #undef GG_RETURN_NULL_IF_NOT_NULL
#endif

#ifdef GG_RETURN_NULL_IF_NOT_NULL_ASSERT
    #undef GG_RETURN_NULL_IF_NOT_NULL_ASSERT
#endif

#ifdef GG_RETURN_NULL_IF_NULL
    #undef GG_RETURN_NULL_IF_NULL
#endif

#ifdef GG_RETURN_NULL_IF_NULL_ASSERT
    #undef GG_RETURN_NULL_IF_NULL_ASSERT
#endif

#ifdef GG_RETURN_NULL_IF_TRUE
    #undef GG_RETURN_NULL_IF_TRUE
#endif

#ifdef GG_RETURN_NULL_IF_TRUE_ASSERT
    #undef GG_RETURN_NULL_IF_TRUE_ASSERT
#endif

#ifdef GG_RETURN_TRUE_IF_FALSE
    #undef GG_RETURN_TRUE_IF_FALSE
#endif

#ifdef GG_RETURN_TRUE_IF_FALSE_ASSERT
    #undef GG_RETURN_TRUE_IF_FALSE_ASSERT
#endif

#ifdef GG_RETURN_TRUE_IF_NOT_NULL
    #undef GG_RETURN_TRUE_IF_NOT_NULL
#endif

#ifdef GG_RETURN_TRUE_IF_NOT_NULL_ASSERT
    #undef GG_RETURN_TRUE_IF_NOT_NULL_ASSERT
#endif

#ifdef GG_RETURN_TRUE_IF_NULL
    #undef GG_RETURN_TRUE_IF_NULL
#endif

#ifdef GG_RETURN_TRUE_IF_NULL_ASSERT
    #undef GG_RETURN_TRUE_IF_NULL_ASSERT
#endif

#ifdef GG_RETURN_TRUE_IF_TRUE
    #undef GG_RETURN_TRUE_IF_TRUE
#endif

#ifdef GG_RETURN_TRUE_IF_TRUE_ASSERT
    #undef GG_RETURN_TRUE_IF_TRUE_ASSERT
#endif

#ifdef GG_RETURN_VALUE_IF_FALSE
    #undef GG_RETURN_VALUE_IF_FALSE
#endif

#ifdef GG_RETURN_VALUE_IF_FALSE_ASSERT
    #undef GG_RETURN_VALUE_IF_FALSE_ASSERT
#endif

#ifdef GG_RETURN_VALUE_IF_NOT_NULL
    #undef GG_RETURN_VALUE_IF_NOT_NULL
#endif

#ifdef GG_RETURN_VALUE_IF_NOT_NULL_ASSERT
    #undef GG_RETURN_VALUE_IF_NOT_NULL_ASSERT
#endif

#ifdef GG_RETURN_VALUE_IF_NULL
    #undef GG_RETURN_VALUE_IF_NULL
#endif

#ifdef GG_RETURN_VALUE_IF_NULL_ASSERT
    #undef GG_RETURN_VALUE_IF_NULL_ASSERT
#endif

#ifdef GG_RETURN_VALUE_IF_TRUE
    #undef GG_RETURN_VALUE_IF_TRUE
#endif

#ifdef GG_RETURN_VALUE_IF_TRUE_ASSERT
    #undef GG_RETURN_VALUE_IF_TRUE_ASSERT
#endif

#ifdef GG_UNUSED
    #undef GG_UNUSED
#endif

#ifdef GG_UNUSED_ARGUMENT
    #undef GG_UNUSED_ARGUMENT
#endif

#ifdef GG_UNUSED_IN_DEBUG
    #undef GG_UNUSED_IN_DEBUG
#endif

#ifdef GG_UNUSED_ARGUMENT_IN_DEBUG
    #undef GG_UNUSED_ARGUMENT_IN_DEBUG
#endif

#ifdef GG_UNUSED_IN_RELEASE
    #undef GG_UNUSED_IN_RELEASE
#endif

#ifdef GG_UNUSED_ARGUMENT_IN_RELEASE
    #undef GG_UNUSED_ARGUMENT_IN_RELEASE
#endif

// define macros

#define GG_DO_IF_FALSE(test, execute)               \
    {                                               \
        if (!(test))                                \
        {                                           \
            execute;                                \
        }                                           \
    }

#define GG_DO_IF_FALSE_ASSERT(test, execute)        \
    {                                               \
        if (!(test))                                \
        {                                           \
            GG_ASSERT_FAILED();                     \
            execute;                                \
        }                                           \
    }

#define GG_DO_IF_NOT_NULL(test, execute)            \
    {                                               \
        if (nullptr != (test))                      \
        {                                           \
            execute;                                \
        }                                           \
    }

#define GG_DO_IF_NOT_NULL_ASSERT(test, execute)     \
    {                                               \
        if (nullptr != (test))                      \
        {                                           \
            GG_ASSERT_FAILED();                     \
            execute;                                \
        }                                           \
    }

#define GG_DO_IF_NULL(test, execute)                \
    {                                               \
        if (nullptr == (test))                      \
        {                                           \
            execute;                                \
        }                                           \
    }

#define GG_DO_IF_NULL_ASSERT(test, execute)         \
    {                                               \
        if (nullptr == (test))                      \
        {                                           \
            GG_ASSERT_FAILED();                     \
            execute;                                \
        }                                           \
    }

#define GG_DO_IF_TRUE(test, execute)                \
    {                                               \
        if (test)                                   \
        {                                           \
            execute;                                \
        }                                           \
    }

#define GG_DO_IF_TRUE_ASSERT(test, execute)         \
    {                                               \
        if (test)                                   \
        {                                           \
            GG_ASSERT_FAILED();                     \
            execute;                                \
        }                                           \
    }

#define GG_CONTINUE_IF_FALSE(test)                      \
    GG_DO_IF_FALSE(test, continue)
#define GG_CONTINUE_IF_FALSE_ASSERT(test)               \
    GG_DO_IF_FALSE_ASSERT(test, continue)
#define GG_CONTINUE_IF_NOT_NULL(test)                   \
    GG_DO_IF_NOT_NULL(test, continue)
#define GG_CONTINUE_IF_NOT_NULL_ASSERT(test)            \
    GG_DO_IF_NOT_NULL_ASSERT(test, continue)
#define GG_CONTINUE_IF_NULL(test)                       \
    GG_DO_IF_NULL(test, continue)
#define GG_CONTINUE_IF_NULL_ASSERT(test)                \
    GG_DO_IF_NULL_ASSERT(test, continue)
#define GG_CONTINUE_IF_TRUE(test)                       \
    GG_DO_IF_TRUE(test, continue)
#define GG_CONTINUE_IF_TRUE_ASSERT(test)                \
    GG_DO_IF_TRUE_ASSERT(test, continue)

#define GG_RETURN_IF_FALSE(test)                        \
    GG_DO_IF_FALSE(test, return)
#define GG_RETURN_IF_FALSE_ASSERT(test)                 \
    GG_DO_IF_FALSE_ASSERT(test, return)
#define GG_RETURN_IF_NOT_NULL(test)                     \
    GG_DO_IF_NOT_NULL(test, return)
#define GG_RETURN_IF_NOT_NULL_ASSERT(test)              \
    GG_DO_IF_NOT_NULL_ASSERT(test, return)
#define GG_RETURN_IF_NULL(test)                         \
    GG_DO_IF_NULL(test, return)
#define GG_RETURN_IF_NULL_ASSERT(test)                  \
    GG_DO_IF_NULL_ASSERT(test, return)
#define GG_RETURN_IF_TRUE(test)                         \
    GG_DO_IF_TRUE(test, return)
#define GG_RETURN_IF_TRUE_ASSERT(test)                  \
    GG_DO_IF_TRUE_ASSERT(test, return)

#define GG_RETURN_FALSE_IF_FALSE(test)                  \
    GG_DO_IF_FALSE(test, return false)
#define GG_RETURN_FALSE_IF_FALSE_ASSERT(test)           \
    GG_DO_IF_FALSE_ASSERT(test, return false)
#define GG_RETURN_FALSE_IF_NOT_NULL(test)               \
    GG_DO_IF_NOT_NULL(test, return false)
#define GG_RETURN_FALSE_IF_NOT_NULL_ASSERT(test)        \
    GG_DO_IF_NOT_NULL_ASSERT(test, return false)
#define GG_RETURN_FALSE_IF_NULL(test)                   \
    GG_DO_IF_NULL(test, return false)
#define GG_RETURN_FALSE_IF_NULL_ASSERT(test)            \
    GG_DO_IF_NULL_ASSERT(test, return false)
#define GG_RETURN_FALSE_IF_TRUE(test)                   \
    GG_DO_IF_TRUE(test, return false)
#define GG_RETURN_FALSE_IF_TRUE_ASSERT(test)            \
    GG_DO_IF_TRUE_ASSERT(test, return false)

#define GG_RETURN_NULL_IF_FALSE(test)                   \
    GG_DO_IF_FALSE(test, return nullptr)
#define GG_RETURN_NULL_IF_FALSE_ASSERT(test)            \
    GG_DO_IF_FALSE_ASSERT(test, return nullptr)
#define GG_RETURN_NULL_IF_NOT_NULL(test)                \
    GG_DO_IF_NOT_NULL(test, return nullptr)
#define GG_RETURN_NULL_IF_NOT_NULL_ASSERT(test)         \
    GG_DO_IF_NOT_NULL_ASSERT(test, return nullptr)
#define GG_RETURN_NULL_IF_NULL(test)                    \
    GG_DO_IF_NULL(test, return nullptr)
#define GG_RETURN_NULL_IF_NULL_ASSERT(test)             \
    GG_DO_IF_NULL_ASSERT(test, return nullptr)
#define GG_RETURN_NULL_IF_TRUE(test)                    \
    GG_DO_IF_TRUE(test, return nullptr)
#define GG_RETURN_NULL_IF_TRUE_ASSERT(test)             \
    GG_DO_IF_TRUE_ASSERT(test, return nullptr)

#define GG_RETURN_TRUE_IF_FALSE(test)                   \
    GG_DO_IF_FALSE(test, return true)
#define GG_RETURN_TRUE_IF_FALSE_ASSERT(test)            \
    GG_DO_IF_FALSE_ASSERT(test, return true)
#define GG_RETURN_TRUE_IF_NOT_NULL(test)                \
    GG_DO_IF_NOT_NULL(test, return true)
#define GG_RETURN_TRUE_IF_NOT_NULL_ASSERT(test)         \
    GG_DO_IF_NOT_NULL_ASSERT(test, return true)
#define GG_RETURN_TRUE_IF_NULL(test)                    \
    GG_DO_IF_NULL(test, return true)
#define GG_RETURN_TRUE_IF_NULL_ASSERT(test)             \
    GG_DO_IF_NULL_ASSERT(test, return true)
#define GG_RETURN_TRUE_IF_TRUE(test)                    \
    GG_DO_IF_TRUE(test, return true)
#define GG_RETURN_TRUE_IF_TRUE_ASSERT(test)             \
    GG_DO_IF_TRUE_ASSERT(test, return true)

#define GG_RETURN_VALUE_IF_FALSE(test, value)           \
    GG_DO_IF_FALSE(test, return value)
#define GG_RETURN_VALUE_IF_FALSE_ASSERT(test, value)    \
    GG_DO_IF_FALSE_ASSERT(test, return value)
#define GG_RETURN_VALUE_IF_NOT_NULL(test, value)        \
    GG_DO_IF_NOT_NULL(test, return value)
#define GG_RETURN_VALUE_IF_NOT_NULL_ASSERT(test, value) \
    GG_DO_IF_NOT_NULL_ASSERT(test, return value)
#define GG_RETURN_VALUE_IF_NULL(test, value)            \
    GG_DO_IF_NULL(test, return value)
#define GG_RETURN_VALUE_IF_NULL_ASSERT(test, value)     \
    GG_DO_IF_NULL_ASSERT(test, return value)
#define GG_RETURN_VALUE_IF_TRUE(test, value)            \
    GG_DO_IF_TRUE(test, return value)
#define GG_RETURN_VALUE_IF_TRUE_ASSERT(test, value)     \
    GG_DO_IF_TRUE_ASSERT(test, return value)

#define GG_UNUSED(variable)                             { (void) variable; }
#define GG_UNUSED_ARGUMENT(variable)

#if defined(GG_DEBUG)

    #define GG_UNUSED_IN_DEBUG(variable)                \
        GG_UNUSED(variable)
    #define GG_UNUSED_ARGUMENT_IN_DEBUG(variable)       \
        GG_UNUSED_ARGUMENT(variable)

    #define GG_UNUSED_IN_RELEASE(variable)
    #define GG_UNUSED_ARGUMENT_IN_RELEASE(variable)     variable

#else

    #define GG_UNUSED_IN_DEBUG(variable)
    #define GG_UNUSED_ARGUMENT_IN_DEBUG(variable)       variable

    #define GG_UNUSED_IN_RELEASE(variable)              \
        GG_UNUSED(variable)
    #define GG_UNUSED_ARGUMENT_IN_RELEASE(variable)     \
        GG_UNUSED_ARGUMENT(variable)

#endif

#endif // _gg_macro_h_
