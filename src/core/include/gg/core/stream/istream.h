#ifndef _gg_istream_h_
#define _gg_istream_h_

#include "gg/core/endian/endian.h"
#include "gg/core/type/type_trait.h"
#include "gg/core/utils/byte_swap.h"

namespace gg
{
    template <typename STREAM_TYPE>
    class istream
    {
    public:

        // methods

        template <typename TYPE>
        uint32 read(TYPE & value) noexcept
        {
            GG_ASSERT(type::cast_dynamic<STREAM_TYPE *>(this));
            STREAM_TYPE * stream = type::cast_static<STREAM_TYPE *>(this);
            uint32 size = stream->read(&value, sizeof(TYPE));
            if ((size > 0) && !is_endian_mode(endian::system_mode))
            {
                value = swap(value);
            }
            return size;
        }

        // inquiries

        bool8 is_endian_mode(endian_mode mode) const noexcept
        {
            return m_endian_mode == mode;
        }

    protected:

        // constructors

        istream(endian_mode endian_mode = endian::system_mode) noexcept
            : m_endian_mode(endian_mode)
        {
        }
        ~istream(void) noexcept = default;

    private:

        // methods

        template <typename TYPE>
        TYPE swap(TYPE value) noexcept
        {
            return byte_swap::swap(value);
        }

        template <>
        float32 swap<float32>(float32 value) noexcept
        {
            union { float32 as_float; uint32  as_unsigned; } temp;
            temp.as_float = value;
            temp.as_unsigned = byte_swap::swap(temp.as_unsigned);
            return temp.as_float;
        }

        template <>
        float64 swap<float64>(float64 value) noexcept
        {
            union { float64 as_float; uint64  as_unsigned; } temp;
            temp.as_float = value;
            temp.as_unsigned = byte_swap::swap(temp.as_unsigned);
            return temp.as_float;
        }

    private:

        // attributes

        endian_mode m_endian_mode;
    };
}

#endif // _gg_istream_h_
