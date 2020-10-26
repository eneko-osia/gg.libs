#ifndef _gg_singleton_automatic_h_
#define _gg_singleton_automatic_h_

#include "gg/core/pattern/singleton/singleton_manual.h"

namespace gg
{
    template <typename SINGLETON_TYPE>
    class singleton_automatic : protected singleton_manual<SINGLETON_TYPE>
    {
    public:

        // type definitions

        using singleton_manual<SINGLETON_TYPE>::singleton_type;

        // static accessors

        static singleton_type & get_instance(void) noexcept
        {
            return get_instance<singleton_type>();
        }

        template <typename TYPE>
        static TYPE & get_instance(void) noexcept
        {
            if (!is_available()) { create(); }
            return singleton_manual<SINGLETON_TYPE>::get_instance<TYPE>();
        }

    protected:

        // constructors

        singleton_automatic(void) noexcept = default;
        ~singleton_automatic(void) noexcept
        {
            destroy();
        }
    };
}

#endif // _gg_singleton_automatic_h_

