
#ifndef _gg_gfx_vulkan_context_h_
#define _gg_gfx_vulkan_context_h_

// undefined previous definitions

#ifdef GG_VULKAN_VALIDATION_ENABLED
    #undef GG_VULKAN_VALIDATION_ENABLED
#endif

// define vulkan validation enabled

#if defined(GG_DEBUG)
    #define GG_VULKAN_VALIDATION_ENABLED 1
#else
    #define GG_VULKAN_VALIDATION_ENABLED 0
#endif

// include files

#include "gg/gfx/context.h"
#include <vulkan/vulkan.h>

// namespace

namespace gg::gfx
{
    // class in charge of define vulkan context

    class vulkan_context final : public context
    {
    public:

        // constructors

        vulkan_context(void) noexcept;
        ~vulkan_context(void) noexcept = default;

        // context override methods

        void on_finalize(void) noexcept override;
        bool8 on_init(void) noexcept override;

    private:

        VkDevice m_device;
        VkInstance m_instance;

    #if GG_VULKAN_VALIDATION_ENABLED
        VkDebugUtilsMessengerEXT m_messenger;
    #endif
    };
}

#endif // _gg_gfx_vulkan_context_h_
