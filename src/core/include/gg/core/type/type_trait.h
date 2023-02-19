#ifndef _gg_type_trait_h_
#define _gg_type_trait_h_

#include "gg/core/type/type.h"

#include <functional>
#include <type_traits>
#include <utility>

namespace gg::type
{
    namespace impl
    {
        // structs

        struct equality {};
        template <typename TYPE>
        equality operator==(TYPE const &, TYPE const &);

        template <typename TYPE>
        struct has_equality
        {
            enum
            {
                value =
                    !std::is_same<
                        decltype(
                            *static_cast<TYPE *>(nullptr) ==
                            *static_cast<TYPE *>(nullptr)),
                        equality>::value
            };
        };
    }

    // structs

    template <typename TYPE>
    struct has_equality
    {
        static constexpr bool8 value =
            impl::has_equality<TYPE>::value;
    };

    template <typename TYPE>
    struct has_trivial_assign
    {
        static constexpr bool8 value =
            std::is_trivially_assignable<TYPE, TYPE>::value;
    };

    template <typename TYPE>
    struct has_trivial_constructor
    {
        static constexpr bool8 value =
            std::is_trivially_constructible<TYPE>::value;
    };

    template <typename TYPE>
    struct has_trivial_copy
    {
        static constexpr bool8 value =
            std::is_trivially_copy_constructible<TYPE>::value;
    };

    template <typename TYPE>
    struct has_trivial_destructor
    {
        static constexpr bool8 value =
            std::is_trivially_destructible<TYPE>::value;
    };

    template <typename TYPE>
    struct is_assignable
    {
        static constexpr bool8 value =
            std::is_copy_assignable<TYPE>::value;
    };

    template <typename TYPE>
    struct is_const
    {
        static constexpr bool8 value = std::is_const<TYPE>::value;
    };

    template <typename TYPE, typename... ARGS>
    struct is_constructible
    {
        static constexpr bool8 value =
            std::is_constructible<TYPE, ARGS...>::value;
    };

    template <typename TYPE>
    struct is_copyable
    {
        static constexpr bool8 value =
            std::is_copy_constructible<TYPE>::value;
    };

    template <typename TYPE>
    struct is_destructible
    {
        static constexpr bool8 value =
            std::is_destructible<TYPE>::value;
    };

    template <typename TYPE>
    struct is_pod
    {
        static constexpr bool8 value =
            std::is_standard_layout<TYPE>::value &&
            std::is_trivial<TYPE>::value;
    };

    template <typename TYPE>
    struct is_pointer
    {
        static constexpr bool8 value = std::is_pointer<TYPE>::value;
    };

    template <typename TYPE>
    struct is_polymorphic
    {
        static constexpr bool8 value = std::is_polymorphic<TYPE>::value;
    };

    // using

    template <bool8 TEST, typename TYPE1, typename TYPE2>
    using conditional = std::conditional<TEST, TYPE1, TYPE2>;

    template<bool8 TEST, typename TYPE = void>
    using enable_if = std::enable_if<TEST, TYPE>;

    template<bool8 TEST, typename TYPE = void>
    using enable_if_t = typename enable_if<TEST, TYPE>::type;

    // methods

    template <typename TO, typename FROM>
    inline
    constexpr TO cast_const(FROM const & value) noexcept
    {
        return const_cast<TO>(value);
    }

    template <typename TO, typename FROM>
    inline
    constexpr TO cast_dynamic(FROM const & value) noexcept
    {
        return dynamic_cast<TO>(value);
    }

    template <typename TO, typename FROM>
    inline
    constexpr TO cast_reinterpret(FROM const & value) noexcept
    {
        return reinterpret_cast<TO>(value);
    }

    template <typename TO, typename FROM>
    inline
    constexpr TO cast_static(FROM const & value) noexcept
    {
        return static_cast<TO>(value);
    }

    template <typename TYPE>
    inline
    constexpr TYPE &&
    forward(typename std::remove_reference<TYPE>::type & args) noexcept
    {
        return std::forward<TYPE>(args);
    }

    template <typename TYPE>
    inline
    constexpr TYPE &&
    forward(typename std::remove_reference<TYPE>::type && args) noexcept
    {
        return std::forward<TYPE>(args);
    }

    template <typename TYPE>
    inline
    constexpr typename std::remove_reference<TYPE>::type &&
    move(TYPE && args) noexcept
    {
        return std::move(args);
    }

    template <typename TYPE>
    inline std::reference_wrapper<TYPE> ref(TYPE & value) noexcept
    {
        return std::ref<TYPE>(value);
    }
}

#endif // _gg_type_trait_h_
