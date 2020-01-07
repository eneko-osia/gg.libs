#ifndef _gg_string_ref_h_
#define _gg_string_ref_h_

// include files

#include "gg/core/macro/macro.h"
#include "gg/core/string/type/string.h"
#include "gg/core/type/type_trait.h"

// namespace

namespace gg
{
    // class in charge of define a reference string

    class string_ref final
    {
    public:

        // constructors

        constexpr string_ref(void)
            : m_data(nullptr)
        {
        }

        constexpr string_ref(string_ref const & string) noexcept
            : m_data(nullptr)
        {
            set(string);
        }

        constexpr string_ref(string_ref && string) noexcept
            : m_data(nullptr)
        {
            set(type::move(string));
        }

        template <typename STRING_TYPE>
        constexpr string_ref(STRING_TYPE const & string)
            : m_data(nullptr)
        {
            set(string);
        }

        ~string_ref(void) = default;

        // operators

        char8 const & operator[](size_type idx) const noexcept
        {
            GG_ASSERT_LESS_THAN(idx, size());
            return begin()[idx];
        }

        constexpr string_ref & operator=(char8 const * string) noexcept
        {
            return set(string);
        }

        constexpr string_ref & operator=(string_ref const & string) noexcept
        {
            return set(string);
        }

        constexpr string_ref & operator=(string_ref && string) noexcept
        {
            return set(type::move(string));
        }

        template <typename STRING_TYPE>
        constexpr string_ref & operator=(STRING_TYPE const & string) noexcept
        {
            return set(string);
        }

        bool8 operator==(char8 const * string) const noexcept
        {
            return string::compare(begin(), string) == 0;
        }

        template <typename STRING_TYPE>
        bool8 operator==(STRING_TYPE const & string) const noexcept
        {
            return *this == string.begin();
        }

        bool8 operator!=(char8 const * string) const noexcept
        {
            return !(*this == string);
        }

        template <typename STRING_TYPE>
        bool8 operator!=(STRING_TYPE const & string) const noexcept
        {
            return !(*this == string);
        }

        bool8 operator<(char8 const * string) const noexcept
        {
            return string::compare(begin(), string) < 0;
        }

        template <typename STRING_TYPE>
        bool8 operator<(STRING_TYPE const & string) const noexcept
        {
            return *this < string.begin();
        }

        bool8 operator>(char8 const * string) const noexcept
        {
            return string::compare(begin(), string) > 0;
        }

        template <typename STRING_TYPE>
        bool8 operator>(STRING_TYPE const & string) const noexcept
        {
            return *this > string.begin();
        }

        // methods

        constexpr char8 const * begin(void) const noexcept
        {
            return m_data;
        }

        constexpr void clear(void) noexcept
        {
            m_data = nullptr;
        }

        char8 const * end(void) const noexcept
        {
            return begin() + size();
        }

        size_type find(char8 const * string, size_type idx = 0) const noexcept
        {
            GG_ASSERT_LESS_THAN(idx, size());
            char8 const * position = string::find(begin() + idx, string);
            return size_type(
                nullptr == position ? string::npos : position - begin());
        }

        template <typename STRING_TYPE>
        size_type
        find(STRING_TYPE const & string, size_type idx = 0) const noexcept
        {
            return find(string.begin(), idx);
        }

        constexpr string_ref & set(char8 * string) noexcept
        {
            return set(type::cast_const<char8 const *>(string));
        }

        constexpr string_ref & set(char8 const * string) noexcept
        {
            m_data = string;
            return *this;
        }

        constexpr string_ref & set(string_ref const & string) noexcept
        {
            GG_ASSERT_NOT_EQUALS(this, &string);
            m_data = string.m_data;
            return *this;
        }

        constexpr string_ref & set(string_ref && string) noexcept
        {
            GG_ASSERT_NOT_EQUALS(this, &string);
            m_data = type::move(string.m_data);
            string.m_data = nullptr;

            return *this;
        }

        template <typename STRING_TYPE>
        constexpr string_ref & set(STRING_TYPE const & string) noexcept
        {
            return set(string.begin());
        }

        size_type size(void) const noexcept
        {
            return begin() ? size_type(string::length(begin())) : 0;
        }

        // inquiries

        bool8 is_empty(void) const noexcept
        {
            return 0 == size();
        }

    private:

        // attributes

        char8 const * m_data;
    };

    // helpers

    inline bool8 operator<(char8 const * lstring, string_ref const & rstring)
    {
        return rstring > lstring;
    }

    inline bool8 operator>(char8 const * lstring, string_ref const & rstring)
    {
        return rstring < lstring;
    }

    inline bool8 operator==(char8 const * lstring, string_ref const & rstring)
    {
        return rstring == lstring;
    }

    inline bool8 operator!=(char8 const * lstring, string_ref const & rstring)
    {
        return rstring != lstring;
    }
}

#endif // _gg_string_ref_h_
