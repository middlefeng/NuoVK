//
//  NuoVulkanPhysicalDevice.hpp
//  Cube-macOS
//
//  Created by middleware on 5/21/18.
//

#ifndef NuoVulkanPhysicalDevice_hpp
#define NuoVulkanPhysicalDevice_hpp


#include "NuoVulkanInstance.h"

#include <vulkan/vulkan.h>


class NuoVulkanDevice;
class NuoVulkanSurface;

typedef std::shared_ptr<NuoVulkanDevice> PNuoVulkanDevice;
typedef std::shared_ptr<NuoVulkanSurface> PNuoVulkanSurface;


class NuoVulkanPhysicalDevice : public std::enable_shared_from_this<NuoVulkanPhysicalDevice>
{

private:
    
    std::shared_ptr<NuoVulkanInstance> _instance;
    
    VkPhysicalDevice _vkPhysicalDevice;
    VkPhysicalDeviceProperties _properties;
    std::vector<VkQueueFamilyProperties> _queueFamilyProperties;
    
    std::vector<std::string> _extensions;
    std::vector<const char*> _extensionsDesired;
    
    NuoVulkanPhysicalDevice() = delete;
    
    void CacheProperties();
    void CacheQueueFamilyProperties();
    void QueryExtensions();

public:
    
    NuoVulkanPhysicalDevice(const std::shared_ptr<NuoVulkanInstance>& instance,
                            VkPhysicalDevice vkPhysicalDevice);
    ~NuoVulkanPhysicalDevice();
    
    VkPhysicalDevice VulkanPhysicalDevice() { return _vkPhysicalDevice; }
    
    const char* Name();
    PNuoVulkanDevice CreateDevice(const PNuoVulkanSurface& surface);
    
    uint32_t QueueFamiliesCount();
    bool QueueFamilySupportGraphics(uint32_t index);
    bool QueueFamilySupportPresent(uint32_t index, const PNuoVulkanSurface& surface);
    
};

#endif /* NuoVulkanPhysicalDevice_hpp */
