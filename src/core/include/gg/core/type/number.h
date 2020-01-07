#ifndef _gg_number_h_
#define _gg_number_h_

// include files

#include "gg/core/type/type_trait.h"

// namespace

namespace gg
{
    // class in charge of define a number

    template <typename ACTUAL_TYPE, typename STORAGE_TYPE>
    class number
    {
    public:

        // type definitions

        typedef ACTUAL_TYPE actual_type;
        typedef STORAGE_TYPE storage_type;

        // constructors

        number(void) = default;
        number(number const & value) = default;

        number(storage_type value) : m_value(value)
        {
        }

        // operators

        actual_type & operator+(void)
        {
            return *type::cast_static<actual_type *>(this);
        }

        actual_type operator+(actual_type const & value) const
        {
            return actual_type(m_value + value.m_value);
        }

        actual_type & operator+=(actual_type const & value)
        {
            m_value += value.m_value;
            return *type::cast_static<actual_type *>(this);
        }

        actual_type & operator-(void)
        {
            m_value = -m_value;
            return *type::cast_static<actual_type *>(this);
        }

        actual_type operator-(actual_type const & value) const
        {
            return actual_type(m_value - value.m_value);
        }

        actual_type & operator-=(actual_type const & value)
        {
            m_value -= value.m_value;
            return *type::cast_static<actual_type *>(this);
        }

        actual_type operator*(actual_type const & value) const
        {
            return actual_type(m_value * value.m_value);
        }

        actual_type & operator*=(actual_type const & value)
        {
            m_value *= value.m_value;
            return *type::cast_static<actual_type *>(this);
        }

        actual_type operator/(actual_type const & value) const
        {
            return actual_type(m_value / value.m_value);
        }

        actual_type & operator/=(actual_type const & value)
        {
            m_value /= value.m_value;
            return *type::cast_static<actual_type *>(this);
        }

        actual_type & operator=(actual_type const & value)
        {
            m_value = value.m_value;
            return *type::cast_static<actual_type *>(this);
        }

        bool8 operator==(actual_type const & value) const
        {
            return m_value == value.m_value;
        }

        bool8 operator!=(actual_type const & value) const
        {
            return m_value != value.m_value;
        }

        bool8 operator<(actual_type const & value) const
        {
            return m_value < value.m_value;
        }

        bool8 operator<=(actual_type const & value) const
        {
            return m_value <= value.m_value;
        }

        bool8 operator>(actual_type const & value) const
        {
            return m_value > value.m_value;
        }

        bool8 operator>=(actual_type const & value) const
        {
            return m_value >= value.m_value;
        }

        // methods

        storage_type get(void) const
        {
            return m_value;
        }

    protected:

        // constructors

        ~number(void) = default;

    private:

        // attributes

        storage_type m_value;
    };
}

#endif // _gg_number_h_
