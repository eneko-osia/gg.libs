#ifndef _gg_string_static_h_
#define _gg_string_static_h_

// include files

#include "gg/core/container/array/array_static.h"
#include "gg/core/string/type/string.h"

// namespace

namespace gg
{
    // class in charge of define a static string

    template <size_type MAX_SIZE = 16>
    class string_static final
    {
    private:

        // type definitions

        typedef array_static<char8, MAX_SIZE> data_type;

    public:

        // constructors

        string_static(void) noexcept
            : m_data()
        {
            set("");
        }

        string_static(string_static const & string) noexcept
            : m_data()
        {
            set(string);
        }

        template <typename STRING_TYPE>
        string_static(const STRING_TYPE & string) noexcept
            : m_data()
        {
            set(string);
        }

        ~string_static(void) = default;

        // operators

        char8 & operator[](size_type idx) noexcept
        {
            return m_data[idx];
        }

        char8 const & operator[](size_type idx) const noexcept
        {
            return m_data[idx];
        }

        string_static & operator=(char8 const * string) noexcept
        {
            return set(string);
        }

        string_static & operator=(string_static const & string) noexcept
        {
            return set(string);
        }

        template <typename STRING_TYPE>
        string_static & operator=(STRING_TYPE const & string) noexcept
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

        string_static & append(char8 const & character) noexcept
        {
            return append(type::cast_const<char8 const *>(&character), 1);
        }

        string_static & append(char8 const * string) noexcept
        {
            return append(string, size_type(string::length(string)));
        }

        string_static &
        append(char8 const * string, size_type num_char) noexcept
        {
            size_type cur_size = size();
            size_type new_size = limit::min<size_type>(
                cur_size + num_char, max_size() - 1);
            memory::copy(begin() + cur_size, string, new_size - cur_size);
            begin()[new_size] = '\0';
            return *this;
        }

        template <typename STRING_TYPE>
        string_static & append(STRING_TYPE const & string) noexcept
        {
            return append(string.begin(), string.size());
        }

        template <typename STRING_TYPE>
        string_static &
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

        char8 * c_str(void) noexcept
        {
            return begin();
        }

        char8 const * c_str(void) const noexcept
        {
            return begin();
        }

        void clear(void) noexcept
        {
            memory::zero(begin(), size());
        }

        char8 * end(void) noexcept
        {
            return begin() + size();
        }

        char8 const * end(void) const noexcept
        {
            return begin() + size();
        }

        string_static & erase(size_type idx, size_type num_char) noexcept
        {
            GG_ASSERT_LESS_THAN(idx, size());

            size_type cur_size = size();
            size_type end_idx =
                limit::min<size_type>(idx + num_char, cur_size);
            memory::move(begin() + idx, begin() + end_idx, cur_size - end_idx);
            begin()[cur_size - (end_idx - idx)] = '\0';
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

        string_static &
        insert(size_type idx, char8 const & character) noexcept
        {
            return insert(idx, type::cast_const<char8 const *>(&character), 1);
        }

        string_static & insert(size_type idx, char8 const * string) noexcept
        {
            return insert(idx, string, size_type(string::length(string)));
        }

        string_static &
        insert(size_type idx, char8 const * string, size_type num_char) noexcept
        {
            GG_ASSERT_LESS_THAN(idx, size());

            size_type cur_size = size();
            size_type new_size =
                limit::min<size_type>(cur_size + num_char, max_size() - 1);
            size_type end_idx =
                limit::min<size_type>(idx + num_char, new_size);

            memory::move(begin() + end_idx, begin() + idx, new_size - end_idx);
            memory::copy(begin() + idx, string, end_idx - idx);
            begin()[new_size] = '\0';
            return *this;
        }

        template <typename STRING_TYPE>
        string_static &
        insert(size_type idx, STRING_TYPE const & string) noexcept
        {
            return insert(idx, string.begin(), string.size());
        }

        template <typename STRING_TYPE>
        string_static & insert(
            size_type idx,
            STRING_TYPE const & string,
            size_type num_char) noexcept
        {
            return insert(idx, string.begin(), num_char);
        }

        string_static & set(char8 * string) noexcept
        {
            return set(type::cast_const<char8 const *>(string));
        }

        string_static & set(char8 const * string) noexcept
        {
            return set(string, size_type(string::length(string)));
        }

        string_static & set(char8 * string, size_type num_char) noexcept
        {
            return set(type::cast_const<char8 const *>(string), num_char);
        }

        string_static & set(char8 const * string, size_type num_char) noexcept
        {
            size_type new_size =
                limit::min<size_type>(num_char, max_size() - 1);
            memory::copy(begin(), string, new_size);
            begin()[new_size] = '\0';
            return *this;
        }

        string_static &
        set(char8 * string, size_type idx_start, size_type idx_end) noexcept
        {
            return
                set(type::cast_const<char8 const *>(string), idx_start, idx_end);
        }

        string_static & set(
            char8 const * string,
            size_type idx_start,
            size_type idx_end) noexcept
        {
            return set(string + idx_start, idx_end - idx_start + 1);
        }

        string_static & set(string_static const & string) noexcept
        {
            m_data = string.m_data;
            return *this;
        }

        template <typename STRING_TYPE>
        string_static & set(STRING_TYPE const & string) noexcept
        {
            return set(string.begin(), string.size());
        }

        template <typename STRING_TYPE>
        string_static &
        set(STRING_TYPE const & string, size_type num_char) noexcept
        {
            return set(string.begin(), num_char);
        }

        template <typename STRING_TYPE>
        string_static & set(
            STRING_TYPE const & string,
            size_type idx_start,
            size_type idx_end) noexcept
        {
            return set(string.begin(), idx_start, idx_end);
        }

        constexpr size_type max_size(void) const noexcept
        {
            return m_data.size();
        }

        size_type size(void) const noexcept
        {
            return size_type(string::length(begin()));
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

    template <size_type MAX_SIZE>
    inline bool8 operator<(
        char8 const * lstring,
        string_static<MAX_SIZE> const & rstring) noexcept
    {
        return rstring > lstring;
    }

    template <size_type MAX_SIZE>
    inline bool8 operator>(
        char8 const * lstring,
        string_static<MAX_SIZE> const & rstring) noexcept
    {
        return rstring < lstring;
    }

    template <size_type MAX_SIZE>
    inline bool8 operator==(
        char8 const * lstring,
        string_static<MAX_SIZE> const & rstring) noexcept
    {
        return rstring == lstring;
    }

    template <size_type MAX_SIZE>
    inline bool8 operator!=(
        char8 const * lstring,
        string_static<MAX_SIZE> const & rstring) noexcept
    {
        return rstring != lstring;
    }
}

#endif // _gg_string_static_h_
