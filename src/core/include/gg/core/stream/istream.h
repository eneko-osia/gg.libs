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
        size_type read(TYPE & value) noexcept
        {
            GG_ASSERT(type::cast_dynamic<STREAM_TYPE *>(this));
            STREAM_TYPE * stream = type::cast_static<STREAM_TYPE *>(this);
            size_type read_size = stream->read(&value, sizeof(TYPE));
            if ((read_size > 0) && !is_endian_mode(endian::system_mode))
            {
                value = byte_swap::swap(value);
            }
            return read_size;
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

        // attributes

        endian_mode m_endian_mode;
    };
}

#endif // _gg_istream_h_
