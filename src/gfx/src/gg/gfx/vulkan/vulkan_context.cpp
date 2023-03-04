#if defined(GG_GFX_VULKAN_SUPPORT)
//==============================================================================

#include "gg/gfx/vulkan/vulkan_context.h"

//==============================================================================

#include "gg/core/container/array/array_dynamic.h"
#include "gg/core/container/array/array_static.h"
#include "gg/core/version.h"

//==============================================================================
namespace gg::gfx
{
//==============================================================================

// static void get_supported_extensions(array_dynamic<char8 const *> & extensions)
// {
//     uint32 num_properties = 0;
//     vkEnumerateInstanceExtensionProperties(nullptr, &num_properties, nullptr);

//     array_dynamic<VkExtensionProperties> properties;
//     properties.resize(num_properties);
//     vkEnumerateInstanceExtensionProperties(nullptr, &num_properties, properties.data());

//     for (VkExtensionProperties const & property : properties)
//     {
//         extensions.emplace_back(property.extensionName);
//     }
// }

#if GG_VULKAN_VALIDATION_ENABLED
static bool has_validation_support(array_dynamic<char8 const *> const & validations)
{
    static constexpr uint32 k_max_layers = 64;

    uint32 num_layers = 0;
    vkEnumerateInstanceLayerProperties(&num_layers, nullptr);
    GG_RETURN_FALSE_IF(num_layers > k_max_layers);

    array_static<VkLayerProperties, k_max_layers> layers;
    vkEnumerateInstanceLayerProperties(&num_layers, layers.data());

    for (char8 const * layer_name : validations)
    {
        bool found = false;

        for (uint32 i = 0; i < num_layers; ++i)
        {
            if (string::compare(layer_name, layers[i].layerName) == 0)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            return false;
        }
    }

    return true;
}
#endif

#if GG_VULKAN_VALIDATION_ENABLED
static VKAPI_ATTR VkBool32
VKAPI_CALL log_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT severity,
    VkDebugUtilsMessageTypeFlagsEXT GG_UNUSED_ARGUMENT(type),
    const VkDebugUtilsMessengerCallbackDataEXT* GG_UNUSED_ARGUMENT(data),
    void* GG_UNUSED_ARGUMENT(user_data))
{
    switch (severity)
    {
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
        {
            // log::logger::verbose<log::gfx>("validation layer: %s", data->pMessage);
            break;
        }
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
        {
            // log::logger::normal<log::gfx>("validation layer: %s", data->pMessage);
            break;
        }
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
        {
            // log::logger::warning<log::gfx>("validation layer: %s", data->pMessage);
            break;
        }
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
        {
            // log::logger::error<log::gfx>("validation layer: %s", data->pMessage);
            break;
        }
        default:
        {
            break;
        }
    }
    return VK_FALSE;
}
#endif

//==============================================================================

vulkan_context::vulkan_context(void) noexcept
    : m_device()
    , m_instance()
#if GG_VULKAN_VALIDATION_ENABLED
    , m_messenger()
#endif
{
}

//==============================================================================

void vulkan_context::on_finalize(void) noexcept
{
    vkDestroyDevice(m_device, nullptr);

#if GG_VULKAN_VALIDATION_ENABLED
    auto vkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(m_instance, "vkDestroyDebugUtilsMessengerEXT");
    GG_RETURN_IF(!vkDestroyDebugUtilsMessengerEXT);
    vkDestroyDebugUtilsMessengerEXT(m_instance, m_messenger, nullptr);
#endif

    vkDestroyInstance(m_instance, nullptr);
}

bool8 vulkan_context::on_init(context_info_base const * info) noexcept
{
    (void) info;
#if GG_VULKAN_VALIDATION_ENABLED
    array_dynamic<char8 const *> validation;
    validation.emplace_back("VK_LAYER_KHRONOS_validation");
    validation.emplace_back("VK_LAYER_LUNARG_api_dump");
    validation.emplace_back("VK_LAYER_LUNARG_device_simulation");
    validation.emplace_back("VK_LAYER_LUNARG_monitor");
    validation.emplace_back("VK_LAYER_LUNARG_screenshot");
    GG_RETURN_FALSE_IF(!has_validation_support(validation));
#endif

    VkApplicationInfo app_info;
    memory::zero(&app_info);

    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = "gg.engine";
    app_info.applicationVersion =
        VK_MAKE_VERSION(version_major, version_minor, version_patch);
    app_info.pEngineName = "gg.libs";
    app_info.engineVersion =
        VK_MAKE_VERSION(version_major, version_minor, version_patch);
    app_info.apiVersion = VK_API_VERSION_1_0;

    array_dynamic<char8 const *> extensions;
#if GG_VULKAN_VALIDATION_ENABLED
    extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

#if GG_VULKAN_VALIDATION_ENABLED
    VkDebugUtilsMessengerCreateInfoEXT debug_info;
    memory::zero(&debug_info);

    debug_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    debug_info.messageSeverity =
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    debug_info.messageType =
        VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    debug_info.pfnUserCallback = log_callback;
    debug_info.pUserData = nullptr;
#endif

    VkInstanceCreateInfo create_info;
    memory::zero(&create_info);

    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;
    create_info.enabledExtensionCount = uint32(extensions.size());
    create_info.ppEnabledExtensionNames = extensions.data();

#if GG_VULKAN_VALIDATION_ENABLED
    create_info.enabledLayerCount = uint32(validation.size());
    create_info.ppEnabledLayerNames = validation.data();
    create_info.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debug_info;
#endif

    VkResult result = vkCreateInstance(&create_info, nullptr, &m_instance);
    GG_RETURN_FALSE_IF(VK_SUCCESS != result);

#if GG_VULKAN_VALIDATION_ENABLED
    auto vkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(m_instance, "vkCreateDebugUtilsMessengerEXT");
    GG_RETURN_FALSE_IF(!vkCreateDebugUtilsMessengerEXT);
    vkCreateDebugUtilsMessengerEXT(m_instance, &debug_info, nullptr, &m_messenger);
#endif

    VkPhysicalDevice physical_device = VK_NULL_HANDLE;

    static constexpr uint32 k_max_devices = 64;
    uint32 num_physical_devices = 0;
    vkEnumeratePhysicalDevices(m_instance, &num_physical_devices, nullptr);
    GG_RETURN_FALSE_IF(num_physical_devices > k_max_devices);
    array_static<VkPhysicalDevice, k_max_devices> physical_devices;
    vkEnumeratePhysicalDevices(m_instance, &num_physical_devices, physical_devices.data());

    uint32 queue_family_index = 0;
    for (uint32 i = 0; i < num_physical_devices; ++i)
    {
        VkPhysicalDevice const & device = physical_devices[i];

        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(device, &properties);

        if (properties.deviceType != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        {
            continue;
        }

        VkPhysicalDeviceFeatures features;
        vkGetPhysicalDeviceFeatures(device, &features);

        if (!features.geometryShader)
        {
            continue;
        }

        static constexpr uint32 k_max_queue_families = 64;
        uint32 num_queue_families = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &num_queue_families, nullptr);
        GG_RETURN_FALSE_IF(num_queue_families > k_max_queue_families);
        array_static<VkQueueFamilyProperties, k_max_queue_families> queue_families;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &num_queue_families, queue_families.data());

        for (uint32 j = 0; j < num_queue_families; ++j)
        {
            if (queue_families[j].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                physical_device = device;
                queue_family_index = j;
                break;
            }
        }
    }

    GG_RETURN_FALSE_IF(VK_NULL_HANDLE == physical_device);

    float queue_priority = 1.0f;
    VkDeviceQueueCreateInfo queue_create_info;
    memory::zero(&queue_create_info);

    queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_create_info.queueFamilyIndex = queue_family_index;
    queue_create_info.queueCount = 1;
    queue_create_info.pQueuePriorities = &queue_priority;

    VkPhysicalDeviceFeatures device_features;
    memory::zero(&device_features);

    VkDeviceCreateInfo device_create_info{};
    device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_create_info.pQueueCreateInfos = &queue_create_info;
    device_create_info.queueCreateInfoCount = 1;
    device_create_info.pEnabledFeatures = &device_features;
    device_create_info.enabledExtensionCount = 0;

#if GG_VULKAN_VALIDATION_ENABLED
    device_create_info.enabledLayerCount = uint32(validation.size());
    device_create_info.ppEnabledLayerNames = validation.data();
#endif

    VkResult device_result = vkCreateDevice(physical_device, &device_create_info, nullptr, &m_device);
    GG_RETURN_FALSE_IF(VK_SUCCESS != device_result);

    VkQueue graphics_queue;
    vkGetDeviceQueue(m_device, queue_family_index, 0, &graphics_queue);

    return true;
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
