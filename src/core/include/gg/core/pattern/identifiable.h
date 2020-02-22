#ifndef _gg_identifiable_h_
#define _gg_identifiable_h_

// include files

#include "gg/core/type/type_trait.h"

// namespace

namespace gg
{
    // class in charge of define an identifiable object

    template <typename ID_TYPE>
    class identifiable
    {
    public:

        // type definitions

        typedef ID_TYPE id_type;

        // static asserts

        GG_STATIC_ASSERT(
            !type::is_pointer<id_type>(),
            "pointer id_type is not allowed");

        // constructors

        identifiable(void) noexcept
            : m_id()
        {
        }

        identifiable(id_type const & id) noexcept
            : m_id(id)
        {
        }

        identifiable(id_type && id) noexcept
            : m_id(type::move(id))
        {
        }

        identifiable(identifiable const & obj) noexcept
            : m_id(obj.m_id)
        {
        }

        identifiable(identifiable && obj) noexcept
            : m_id(type::move(obj.m_id))
        {
        }

        // accessors

        id_type const & get_id(void) const noexcept
        {
            return m_id;
        }

        void set_id(id_type const & id) noexcept
        {
            m_id = id;
        }

        void set_id(id_type && id) noexcept
        {
            m_id = type::move(id);
        }

        template <typename TYPE>
        void set_id(TYPE && id) noexcept
        {
            m_id = type::forward<TYPE>(id);
        }

        // inquiries

        bool8 is_id(id_type const & id) const noexcept
        {
            return m_id == id;
        }

        template <typename TYPE>
        bool8 is_id(TYPE const & id) const noexcept
        {
            return m_id == id;
        }

    protected:

        // constructors

        ~identifiable(void) noexcept
        {
        }

    private:

        // attributes

        id_type m_id;
    };
}

#endif // _gg_identifiable_h_
