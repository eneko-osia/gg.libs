#ifndef _gg_string_dynamic_h_
#define _gg_string_dynamic_h_

// include files

#include "gg/core/container/array/array_dynamic.h"
#include "gg/core/string/type/string.h"

// namespace

namespace gg
{
    // class in charge of define a dynamic string

    class string_dynamic final
    {
    private:

        // type definitions

        typedef array_dynamic<char8> data_type;

    public:

        // constructors

        string_dynamic(void) noexcept
            : m_data()
        {
        }

        string_dynamic(string_dynamic const & string) noexcept
            : m_data()
        {
            set(string);
        }

        string_dynamic(string_dynamic && string) noexcept
            : m_data()
        {
            set(type::move(string));
        }

        template <typename STRING_TYPE>
        string_dynamic(STRING_TYPE const & string) noexcept
            : m_data()
        {
            set(string);
        }

        ~string_dynamic(void) noexcept = default;

        // operators

        char8 & operator[](size_type idx) noexcept
        {
            return m_data[idx];
        }

        char8 const & operator[](size_type idx) const noexcept
        {
            return m_data[idx];
        }

        string_dynamic & operator=(char8 const * string) noexcept
        {
            return set(string);
        }

        string_dynamic & operator=(string_dynamic const & string) noexcept
        {
            return set(string);
        }

        string_dynamic & operator=(string_dynamic && string) noexcept
        {
            return set(type::move(string));
        }

        template <typename STRING_TYPE>
        string_dynamic & operator=(STRING_TYPE const & string) noexcept
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

        string_dynamic & append(char8 const & character) noexcept
        {
            return
                append(type::cast_const<char8 const *>(&character), 1);
        }

        string_dynamic & append(char8 const * string) noexcept
        {
            return append(string, size_type(string::length(string)));
        }

        string_dynamic &
        append(char8 const * string, size_type num_char) noexcept
        {
            return insert(size(), string, num_char);
        }

        template <typename STRING_TYPE>
        string_dynamic & append(STRING_TYPE const & string) noexcept
        {
            return append(string.begin(), string.size());
        }

        template <typename STRING_TYPE>
        string_dynamic &
        append(STRING_TYPE const & string, size_type num_char) noexcept
        {
            return append(string.begin(), num_char);
        }

        char8 * begin(void) noexcept
        {
            return m_data.data();
        }

        char8 const * begin(void) const noexcept
        {
            return m_data.data();
        }

        void clear(void) noexcept
        {
            m_data.clear();
            m_data.push_back('\0');
        }

        char8 * end(void) noexcept
        {
            return begin() + size();
        }

        char8 const * end(void) const noexcept
        {
            return begin() + size();
        }

        string_dynamic & erase(size_type idx, size_type num_char) noexcept
        {
            m_data.erase(idx, limit::min(idx + num_char, size()));
            return *this;
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

        string_dynamic &
        insert(size_type idx, char8 const & character) noexcept
        {
            return insert(idx, type::cast_const<char8 const *>(&character), 1);
        }

        string_dynamic & insert(size_type idx, char8 const * string) noexcept
        {
            return insert(idx, string, size_type(string::length(string)));
        }

        string_dynamic &
        insert(size_type idx, char8 const * string, size_type num_char) noexcept
        {
            if (num_char > 0)
            {
                m_data.reserve(size() + num_char + 1);
                m_data.insert(idx, string, string + num_char);
                if ('\0' != m_data.back()) { m_data.push_back('\0'); }
            }
            return *this;
        }

        template <typename STRING_TYPE>
        string_dynamic &
        insert(size_type idx, STRING_TYPE const & string) noexcept
        {
            return insert(idx, string.begin(), string.size());
        }

        template <typename STRING_TYPE>
        string_dynamic & insert(
            size_type idx,
            STRING_TYPE const & string,
            size_type num_char) noexcept
        {
            return insert(idx, string.begin(), num_char);
        }

        string_dynamic & set(char8 * string) noexcept
        {
            return set(type::cast_const<char8 const *>(string));
        }

        string_dynamic & set(char8 const * string) noexcept
        {
            return set(string, size_type(string::length(string)));
        }

        string_dynamic & set(char8 * string, size_type num_char) noexcept
        {
            return set(type::cast_const<char8 const *>(string), num_char);
        }

        string_dynamic & set(char8 const * string, size_type num_char) noexcept
        {
            m_data.clear();
            return insert(0u, string, num_char);
        }

        string_dynamic &
        set(char8 * string, size_type idx_start, size_type idx_end) noexcept
        {
            return
                set(type::cast_const<char8 const *>(string), idx_start, idx_end);
        }

        string_dynamic & set(
            char8 const * string,
            size_type idx_start,
            size_type idx_end) noexcept
        {
            return set(string + idx_start, idx_end - idx_start + 1);
        }

        string_dynamic & set(string_dynamic const & string) noexcept
        {
            m_data = string.m_data;
            return *this;
        }

        string_dynamic & set(string_dynamic && string) noexcept
        {
            m_data = type::move(string.m_data);
            return *this;
        }

        template <typename STRING_TYPE>
        string_dynamic & set(STRING_TYPE const & string) noexcept
        {
            return set(string.begin(), string.size());
        }

        template <typename STRING_TYPE>
        string_dynamic &
        set(STRING_TYPE const & string, size_type num_char) noexcept
        {
            return set(string.begin(), num_char);
        }

        template <typename STRING_TYPE>
        string_dynamic & set(
            STRING_TYPE const & string,
            size_type idx_start,
            size_type idx_end) noexcept
        {
            return set(string.begin(), idx_start, idx_end);
        }

        void reserve(size_type max_size) noexcept
        {
            m_data.reserve(max_size);
        }

        void resize(size_type size) noexcept
        {
            m_data.resize(size);
            m_data.push_back('\0');
        }

        size_type max_size(void) const noexcept
        {
            return m_data.max_size();
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

        data_type m_data;
    };

    // helpers

    inline bool8
    operator<(char8 const * lstring, string_dynamic const & rstring) noexcept
    {
        return rstring > lstring;
    }

    inline bool8
    operator>(char8 const * lstring, string_dynamic const & rstring) noexcept
    {
        return rstring < lstring;
    }

    inline bool8
    operator==(char8 const * lstring, string_dynamic const & rstring) noexcept
    {
        return rstring == lstring;
    }

    inline bool8
    operator!=(char8 const * lstring, string_dynamic const & rstring) noexcept
    {
        return rstring != lstring;
    }
}

#endif // _gg_string_dynamic_h_
