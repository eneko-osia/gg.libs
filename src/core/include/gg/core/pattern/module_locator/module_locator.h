#ifndef _gg_module_locator_h_
#define _gg_module_locator_h_

// include files

#include "gg/core/container/map/hash_map.h"
#include "gg/core/pattern/singleton/singleton_manual.h"

// namespace

namespace gg
{
    class module_locator final : public singleton_manual<module_locator>
    {
    public:

        // methods

        template <typename MODULE_TYPE>
        MODULE_TYPE * get(uint32 id) noexcept
        {
            auto it = m_modules.find(id);
            void * module = (it != m_modules.end()) ? it->second : nullptr;
            GG_ASSERT_NOT_NULL(type::cast_reinterpret<MODULE_TYPE *>(module));
            return type::cast_static<MODULE_TYPE *>(module);
        }

        template <typename MODULE_TYPE>
        MODULE_TYPE const * get(uint32 id) const noexcept
        {
            auto it = m_modules.find(id);
            void * module = (it != m_modules.end()) ? it->second : nullptr;
            GG_ASSERT_NOT_NULL(type::cast_reinterpret<MODULE_TYPE const *>(module));
            return type::cast_static<MODULE_TYPE const *>(module);
        }

        void publish(uint32 id, void * module) noexcept;
        void unpublish(uint32 id) noexcept;

        // inquiries

        bool8 has(uint32 id) const noexcept
        {
            return m_modules.has(id);
        }

    private:

        // friendships

        friend class memory;

        // type definitions

        typedef hash_map<uint32, void *> module_map;

        // constructors

        module_locator(void) noexcept = default;
        ~module_locator(void) noexcept = default;

    private:

        // attributes

        module_map m_modules;
    };
}

#endif // _gg_module_locator_h_
