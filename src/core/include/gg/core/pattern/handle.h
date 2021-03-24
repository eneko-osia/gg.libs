#ifndef _gg_handle_h_
#define _gg_handle_h_

#include "gg/core/type/type_trait.h"

namespace gg
{
    class handle
    {
    public:

        // constructors

        handle(void) noexcept
            : m_handle(nullptr)
        {
        }
        ~handle(void) noexcept = default;

        // methods

        template <typename HANDLE_TYPE>
        HANDLE_TYPE get(void) const noexcept
        {
            return type::cast_static<HANDLE_TYPE>(m_handle);
        }

        template <typename HANDLE_TYPE>
        void set(HANDLE_TYPE _handle) noexcept
        {
            m_handle = type::cast_static<void *>(_handle);
        }

    private:

        // attributes

        void * m_handle;
    };
}

#endif // _gg_handle_h_
