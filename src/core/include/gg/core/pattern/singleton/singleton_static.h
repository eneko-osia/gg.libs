#ifndef _gg_static_sigleton_h_
#define _gg_static_sigleton_h_

// include files

#include "gg/core/pattern/non_copyable.h"
#include "gg/core/type/type_trait.h"

// namespace

namespace gg
{
    // class in charge of define a static singleton object

    template <typename SINGLETON_TYPE>
    class singleton_static : public non_copyable
    {
    public:

        // type definitions

        typedef SINGLETON_TYPE singleton_type;

        // static asserts

        GG_ASSERT_STATIC(
            !type::is_pointer<singleton_type>::value,
            "pointer singleton_type is not allowed");

        // static accessors

        static singleton_type & get_instance(void) noexcept
        {
            static singleton_type instance;
            return instance;
        }

    protected:

        // constructors

        singleton_static(void) noexcept = default;
        ~singleton_static(void) noexcept = default;
    };
}

#endif // _gg_static_sigleton_h_
