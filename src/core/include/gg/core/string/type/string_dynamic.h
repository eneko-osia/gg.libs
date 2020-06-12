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

        // type definitions

        typedef typename data_type::item_type       item_type;

        typedef typename data_type::pointer         pointer;
        typedef typename data_type::const_pointer   const_pointer;

        typedef typename data_type::reference       reference;
        typedef typename data_type::const_reference const_reference;

        typedef typename data_type::iterator        iterator;
        typedef typename data_type::const_iterator  const_iterator;

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

        template <typename STRING_TYPE>
        string_dynamic(STRING_TYPE const & string, size_type num_char) noexcept
            : m_data()
        {
            set(string, num_char);
        }

        template <typename STRING_TYPE>
        string_dynamic(
            STRING_TYPE const & string,
            size_type idx_start,
            size_type idx_end) noexcept
            : m_data()
        {
            set(string, idx_start, idx_end);
        }

        ~string_dynamic(void) noexcept = default;

        // operators

        reference operator[](size_type idx) noexcept
        {
            return m_data[idx];
        }

        const_reference operator[](size_type idx) const noexcept
        {
            return m_data[idx];
        }

        string_dynamic & operator=(const_pointer string) noexcept
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

        bool8 operator==(const_pointer string) const noexcept
        {
            return string::compare(c_str(), string) == 0;
        }

        template <typename STRING_TYPE>
        bool8 operator==(STRING_TYPE const & string) const noexcept
        {
            return *this == string.c_str();
        }

        bool8 operator!=(const_pointer string) const noexcept
        {
            return !(*this == string);
        }

        template <typename STRING_TYPE>
        bool8 operator!=(STRING_TYPE const & string) const noexcept
        {
            return !(*this == string);
        }

        bool8 operator<(const_pointer string) const noexcept
        {
            return string::compare(c_str(), string) < 0;
        }

        template <typename STRING_TYPE>
        bool8 operator<(STRING_TYPE const & string) const noexcept
        {
            return *this < string.c_str();
        }

        bool8 operator>(const_pointer string) const noexcept
        {
            return string::compare(c_str(), string) > 0;
        }

        template <typename STRING_TYPE>
        bool8 operator>(STRING_TYPE const & string) const noexcept
        {
            return *this > string.c_str();
        }

        // methods

        string_dynamic & append(const_reference character) noexcept
        {
            return insert(size(), character);
        }

        string_dynamic & append(const_pointer string) noexcept
        {
            return insert(size(), string);
        }

        string_dynamic &
        append(const_pointer string, size_type num_char) noexcept
        {
            return insert(size(), string, num_char);
        }

        // string_dynamic &
        // append(
        //     const_pointer string,
        //     size_type idx_start,
        //     size_type idx_end) noexcept
        // {
        //     return insert(size(), string, idx_start, idx_end);
        // }

        template <typename STRING_TYPE>
        string_dynamic & append(STRING_TYPE const & string) noexcept
        {
            return insert(size(), string);
        }

        template <typename STRING_TYPE>
        string_dynamic &
        append(STRING_TYPE const & string, size_type num_char) noexcept
        {
            return insert(size(), string, num_char);
        }

        // template <typename STRING_TYPE>
        // string_dynamic &
        // append(
        //     STRING_TYPE const & string,
        //     size_type idx_start,
        //     size_type idx_end) noexcept
        // {
        //     return insert(size(), string, idx_start, idx_end);
        // }

        iterator begin(void) noexcept
        {
            return m_data.begin();
        }

        const_iterator begin(void) const noexcept
        {
            return m_data.begin();
        }

        pointer c_str(void) noexcept
        {
            return m_data.data();
        }

        const_pointer c_str(void) const noexcept
        {
            return m_data.data();
        }

        void clear(void) noexcept
        {
            m_data.clear();
        }

        iterator end(void) noexcept
        {
            return begin() + size();
        }

        const_iterator end(void) const noexcept
        {
            return begin() + size();
        }

        string_dynamic & erase(size_type idx, size_type num_char = 1) noexcept
        {
            m_data.erase(idx, limit::min(idx + num_char, size()));
            return *this;
        }

        size_type find(const_pointer string, size_type idx = 0) const noexcept
        {
            GG_RETURN_VALUE_IF_FALSE(idx < size(), string::npos);
            const_pointer position = string::find(c_str() + idx, string);
            return size_type(position ? (position - c_str()) : string::npos);
        }

        template <typename STRING_TYPE>
        size_type
        find(STRING_TYPE const & string, size_type idx = 0) const noexcept
        {
            return find(string.c_str(), idx);
        }

        string_dynamic &
        insert(size_type idx, const_reference character) noexcept
        {
            return insert(idx, type::cast_const<const_pointer>(&character), 1);
        }

        string_dynamic & insert(size_type idx, const_pointer string) noexcept
        {
            return insert(idx, string, string::length(string));
        }

        string_dynamic &
        insert(size_type idx, const_pointer string, size_type num_char) noexcept
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
            return insert(idx, string.c_str(), string.size());
        }

        template <typename STRING_TYPE>
        string_dynamic & insert(
            size_type idx,
            STRING_TYPE const & string,
            size_type num_char) noexcept
        {
            return insert(idx, string.c_str(), num_char);
        }

        string_dynamic & set(pointer string) noexcept
        {
            return set(type::cast_const<const_pointer>(string));
        }

        string_dynamic & set(const_pointer string) noexcept
        {
            return set(string, string::length(string));
        }

        string_dynamic & set(pointer string, size_type num_char) noexcept
        {
            return set(type::cast_const<const_pointer>(string), num_char);
        }

        string_dynamic & set(const_pointer string, size_type num_char) noexcept
        {
            m_data.clear();
            return insert(0u, string, num_char);
        }

        string_dynamic &
        set(pointer string, size_type idx_start, size_type idx_end) noexcept
        {
            return
                set(type::cast_const<const_pointer>(string), idx_start, idx_end);
        }

        string_dynamic & set(
            const_pointer string,
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
            return set(string.c_str(), string.size());
        }

        template <typename STRING_TYPE>
        string_dynamic &
        set(STRING_TYPE const & string, size_type num_char) noexcept
        {
            return set(string.c_str(), num_char);
        }

        template <typename STRING_TYPE>
        string_dynamic & set(
            STRING_TYPE const & string,
            size_type idx_start,
            size_type idx_end) noexcept
        {
            return set(string.c_str(), idx_start, idx_end);
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
            return m_data.is_empty() ? 0 : string::length(c_str());
        }

        // inquiries

        bool8 is_empty(void) const noexcept
        {
            return m_data.is_empty() ? true : ('\0' == m_data[0]);
        }

    private:

        // attributes

        data_type m_data;
    };

    // helpers

    inline bool8
    operator<(
        string_dynamic::const_pointer lstring,
        string_dynamic const & rstring) noexcept
    {
        return rstring > lstring;
    }

    inline bool8
    operator>(
        string_dynamic::const_pointer lstring,
        string_dynamic const & rstring) noexcept
    {
        return rstring < lstring;
    }

    inline bool8
    operator==(
        string_dynamic::const_pointer lstring,
        string_dynamic const & rstring) noexcept
    {
        return rstring == lstring;
    }

    inline bool8
    operator!=(
        string_dynamic::const_pointer lstring,
        string_dynamic const & rstring) noexcept
    {
        return rstring != lstring;
    }
}

#endif // _gg_string_dynamic_h_
