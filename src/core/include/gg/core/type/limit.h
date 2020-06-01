#ifndef _gg_limit_h_
#define _gg_limit_h_

// include files

#include <algorithm>
#include <limits>

// undefined previous definitions

#ifdef max
	#undef max
#endif

#ifdef min
	#undef min
#endif

// namespace

namespace gg
{
    // namespace in charge of define limit utilities

    namespace limit
    {
        // structs

        template <typename TYPE>
        struct numeric
        {
            static constexpr TYPE epsilon(void) noexcept
            {
                return std::numeric_limits<TYPE>::epsilon();
            }

            static constexpr TYPE max(void) noexcept
            {
                return std::numeric_limits<TYPE>::max();
            }

            static constexpr TYPE min(void) noexcept
            {
                return std::numeric_limits<TYPE>::min();
            }
        };

        // methods

        template <typename TYPE>
        inline constexpr TYPE const &
        max(TYPE const & lvalue, TYPE const & rvalue) noexcept
        {
            return std::max<TYPE>(lvalue, rvalue);
        }

        template <typename TYPE>
        inline constexpr TYPE const &
        min(TYPE const & lvalue, TYPE const & rvalue) noexcept
        {
            return std::min<TYPE>(lvalue, rvalue);
        }
    }
}

#endif // _gg_limit_h_
