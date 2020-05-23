#ifndef _gg_bit_field_h_
#define	_gg_bit_field_h_

// include files

#include "gg/core/type/type.h"

// namespace

namespace gg
{
    // namespace in charge of bit field

    namespace bit_field
    {
        // methods

        template <typename BIT_TYPE>
        inline BIT_TYPE add(BIT_TYPE lhs, BIT_TYPE rhs)
        {
            return lhs | rhs;
        }

        template <typename BIT_TYPE>
        inline BIT_TYPE remove(BIT_TYPE lhs, BIT_TYPE rhs)
        {
            return lhs & ~rhs;
        }

        // inquiries

        template <typename BIT_TYPE>
        inline bool8 is_partially_set(BIT_TYPE value, BIT_TYPE mask)
        {
            return (value & mask) != BIT_TYPE(0);
        }

        template <typename BIT_TYPE>
        inline bool8 is_set(BIT_TYPE value, BIT_TYPE mask)
        {
            return (value & mask) == mask;
        }
    };
}

#endif // _gg_bit_field_h_
