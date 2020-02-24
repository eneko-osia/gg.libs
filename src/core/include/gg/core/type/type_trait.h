#ifndef _gg_type_trait_h_
#define _gg_type_trait_h_

// include files

#include "gg/core/debug/assert.h"
#include "gg/core/type/type.h"

#include <functional>
#include <type_traits>
#include <utility>

// namespace

namespace gg
{
    // namespace in charge of define type trait utilities

    namespace type
    {
        namespace impl
        {
            // structs

            struct equality_operator {};
            template <typename TYPE>
            equality_operator operator==(TYPE const &, TYPE const &);

            template <typename TYPE>
            struct no_equality_operator
            {
                enum
                {
                    value =
                        std::is_same<
                            decltype(
                                *static_cast<TYPE *>(nullptr) ==
                                *static_cast<TYPE *>(nullptr)),
                            equality_operator>::value
                };
            };
        }

        // using

        template <bool8 TEST, typename TYPE1, typename TYPE2>
        using conditional = std::conditional<TEST, TYPE1, TYPE2>;

        template<bool8 TEST, typename TYPE = void>
        using enable_if = std::enable_if<TEST, TYPE>;

        template<bool8 TEST, typename TYPE = void>
        using enable_if_t = typename enable_if<TEST, TYPE>::type;

        template <typename TYPE>
        using is_assignable = std::is_copy_assignable<TYPE>;

        template <typename TYPE>
        using is_const = std::is_const<TYPE>;

        template <typename TYPE, typename... ARGS>
        using is_constructible = std::is_constructible<TYPE, ARGS...>;

        template <typename TYPE>
        using is_copyable = std::is_copy_constructible<TYPE>;

        template <typename TYPE>
        using is_destructible = std::is_destructible<TYPE>;

        template <typename TYPE>
        using is_pod = std::is_pod<TYPE>;

        template <typename TYPE>
        using is_pointer = std::is_pointer<TYPE>;

        template <typename TYPE>
        using is_polymorphic = std::is_polymorphic<TYPE>;

        template <typename TYPE>
        // https://docs.microsoft.com/en-us/cpp/extensions/compiler-support-for-type-traits-cpp-component-extensions?view=vs-2019
        struct no_constructor { constexpr static bool8 value = !__has_trivial_constructor(TYPE); };

        template <typename TYPE>
        using no_copy_constructor = std::is_trivially_copy_constructible<TYPE>;

        template <typename TYPE>
        using no_destructor = std::is_trivially_destructible<TYPE>;

        template <typename TYPE>
        using no_equality_operator = impl::no_equality_operator<TYPE>;

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
            GG_ASSERT(value == static_cast<FROM>(static_cast<TO>(value)));
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
}

#endif // _gg_type_trait_h_
