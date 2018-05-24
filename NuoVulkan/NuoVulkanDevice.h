//
//  NuoVulkanDevice.hpp
//  Cube-iOS
//
//  Created by middleware on 5/22/18.
//

#ifndef NuoVulkanDevice_hpp
#define NuoVulkanDevice_hpp


#include <memory>
#include <vector>
#include <vulkan/vulkan.h>


class NuoVulkanPhysicalDevice;
class NuoVulkanShaderModule;
class NuoVulkanDeviceQueue;
class NuoVulkanSurface;
class NuoVulkanSwapChain;

typedef std::shared_ptr<NuoVulkanShaderModule> PNuoVulkanShaderModule;
typedef std::shared_ptr<NuoVulkanDeviceQueue> PNuoVulkanDeviceQueue;
typedef std::shared_ptr<NuoVulkanSwapChain> PNuoVulkanSwapChain;
typedef std::shared_ptr<NuoVulkanPhysicalDevice> PNuoVulkanPhysicalDevice;
typedef std::shared_ptr<NuoVulkanSurface> PNuoVulkanSurface;



class NuoVulkanDevice : public std::enable_shared_from_this<NuoVulkanDevice>
{
    VkDevice _vkDevice;
    PNuoVulkanPhysicalDevice _physicalDevice;
    
    PNuoVulkanSurface _surface;
    VkSurfaceCapabilitiesKHR _surfaceCapabilities;
    std::vector<VkSurfaceFormatKHR> _surfaceFormats;
    
    PNuoVulkanDeviceQueue _deviceQueue;
    
    // the index of the queue in the physical device for which this logic
    // device is created
    //
    uint32_t _queueIndex;

    NuoVulkanDevice() = delete;
    
    void CacheSurfaceCapabilities();
    void CacheSurfaceFormatsInfo();
    
public:
    
    NuoVulkanDevice(const PNuoVulkanPhysicalDevice& physicalDevice,
                    const PNuoVulkanSurface& surface,
                    uint32_t queueIndex,
                    const std::vector<const char*>& extensions);
    ~NuoVulkanDevice();
    
    VkDevice VulkanDevice() { return _vkDevice; }
    
    PNuoVulkanShaderModule CreateShaderModule(const std::string& path);
    PNuoVulkanSwapChain CreateSwapChain(const PNuoVulkanSwapChain& oldChain);
    PNuoVulkanDeviceQueue DeviceQueue();
    
    friend NuoVulkanPhysicalDevice;
    
};

#endif /* NuoVulkanDevice_hpp */
