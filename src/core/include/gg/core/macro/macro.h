#ifndef _gg_macro_h_
#define _gg_macro_h_

#ifdef GG_DO_IF
    #undef GG_DO_IF
#endif

#ifdef GG_CONTINUE_IF
    #undef GG_CONTINUE_IF
#endif

#ifdef GG_RETURN_FALSE_IF
    #undef GG_RETURN_FALSE_IF
#endif

#ifdef GG_RETURN_IF
    #undef GG_RETURN_IF
#endif

#ifdef GG_RETURN_NULL_IF
    #undef GG_RETURN_NULL_IF
#endif

#ifdef GG_RETURN_TRUE_IF
    #undef GG_RETURN_TRUE_IF
#endif

#ifdef GG_RETURN_VALUE_IF
    #undef GG_RETURN_VALUE_IF
#endif

#ifdef GG_UNUSED_ARGUMENT
    #undef GG_UNUSED_ARGUMENT
#endif

#ifdef GG_UNUSED
    #undef GG_UNUSED
#endif

#ifdef GG_UNUSED_ARGUMENT_IN_DEBUG
    #undef GG_UNUSED_ARGUMENT_IN_DEBUG
#endif

#ifdef GG_UNUSED_ARGUMENT_IN_RELEASE
    #undef GG_UNUSED_ARGUMENT_IN_RELEASE
#endif

#ifdef GG_UNUSED_IN_DEBUG
    #undef GG_UNUSED_IN_DEBUG
#endif

#ifdef GG_UNUSED_IN_RELEASE
    #undef GG_UNUSED_IN_RELEASE
#endif

#define GG_DO_IF(test, execute)         { if (test) { execute; } }
#define GG_CONTINUE_IF(test)            GG_DO_IF(test, continue)
#define GG_RETURN_FALSE_IF(test)        GG_DO_IF(test, return false)
#define GG_RETURN_IF(test)              GG_DO_IF(test, return)
#define GG_RETURN_NULL_IF(test)         GG_DO_IF(test, return nullptr)
#define GG_RETURN_TRUE_IF(test)         GG_DO_IF(test, return true)
#define GG_RETURN_VALUE_IF(test, value) GG_DO_IF(test, return value)
#define GG_UNUSED_ARGUMENT(variable)
#define GG_UNUSED(variable)             { (void) variable; }

#if defined(GG_DEBUG)
    #define GG_UNUSED_ARGUMENT_IN_DEBUG(variable)   GG_UNUSED_ARGUMENT(variable)
    #define GG_UNUSED_ARGUMENT_IN_RELEASE(variable) variable
    #define GG_UNUSED_IN_DEBUG(variable)            GG_UNUSED(variable)
    #define GG_UNUSED_IN_RELEASE(variable)
#else
    #define GG_UNUSED_ARGUMENT_IN_DEBUG(variable)   variable
    #define GG_UNUSED_ARGUMENT_IN_RELEASE(variable) GG_UNUSED_ARGUMENT(variable)
    #define GG_UNUSED_IN_DEBUG(variable)
    #define GG_UNUSED_IN_RELEASE(variable)          GG_UNUSED(variable)
#endif

#endif // _gg_macro_h_
