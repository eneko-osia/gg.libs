#ifndef _gg_memory_buffer_static_h_
#define _gg_memory_buffer_static_h_

// include files

#include "gg/core/macro/macro.h"
#include "gg/core/pattern/non_copyable.h"
#include "gg/core/type/type_trait.h"

// namespace

namespace gg
{
    // class in charge of define a static memory buffer

    template <size_type SIZE>
    class memory_buffer_static final : public non_copyable
    {
    public:

        // accessors

        template <typename ITEM_TYPE = void>
        ITEM_TYPE * data(void) noexcept
        {
            void * data = m_data;
            return type::cast_static<ITEM_TYPE *>(data);
        }

        template <typename ITEM_TYPE = void>
        ITEM_TYPE const * data(void) const noexcept
        {
            void const * data = m_data;
            return type::cast_static<ITEM_TYPE const *>(data);
        }

        template <typename ITEM_TYPE = byte>
        ITEM_TYPE & get(size_type idx) noexcept
        {
            GG_ASSERT_LESS_THAN(idx, size<ITEM_TYPE>());
            return data<ITEM_TYPE>()[idx];
        }

        template <typename ITEM_TYPE = byte>
        ITEM_TYPE const & get(size_type idx) const noexcept
        {
            GG_ASSERT_LESS_THAN(idx, size<ITEM_TYPE>());
            return data<ITEM_TYPE>()[idx];
        }

        template <typename ITEM_TYPE = byte>
        size_type size(void) const
        {
            return type::cast_static<size_type>(SIZE / sizeof(ITEM_TYPE));
        }

    private:

        // attributes

        byte m_data[SIZE];
    };
}

#endif // _gg_memory_buffer_static_h_
