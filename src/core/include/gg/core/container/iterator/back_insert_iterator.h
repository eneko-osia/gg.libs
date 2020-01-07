#ifndef _gg_back_insert_iterator_h_
#define _gg_back_insert_iterator_h_

// include files

#include "gg/core/type/type_trait.h"

// namespace

namespace gg
{
    // class in charge of define a back insert iterator

    template <typename CONTAINER_TYPE>
    class back_insert_iterator final
    {
    public:

        // type definitions

        typedef CONTAINER_TYPE container_type;

        // constructors

        back_insert_iterator(container_type & container) noexcept
            : m_container(container)
        {
        }

        // operators

        back_insert_iterator&
        operator=(typename container_type::item_type const & item) noexcept
        {
            m_container.push_back(item);
            return *this;
        }

        back_insert_iterator &
        operator=(typename container_type::item_type && item) noexcept
        {
            m_container.push_back(type::move(item));
            return *this;
        }

        back_insert_iterator & operator*(void) noexcept
        {
            return *this;
        }

        back_insert_iterator & operator++(void) noexcept
        {
            return *this;
        }

        back_insert_iterator operator++(int32) noexcept
        {
            return *this;
        }

    private:

        // attributes

        container_type & m_container;
    };

    // helper functions

    template <typename CONTAINER_TYPE>
    back_insert_iterator<CONTAINER_TYPE>
    back_inserter(CONTAINER_TYPE & container)
    {
        return back_insert_iterator<CONTAINER_TYPE>(container);
    }
}

#endif // _gg_back_insert_iterator_h_
