//
//  NuoVulkanSurface.hpp
//  Cube-macOS
//
//  Created by middleware on 5/22/18.
//

#ifndef NuoVulkanSurface_hpp
#define NuoVulkanSurface_hpp


#include "NuoVulkanInstance.h"

#include <memory>
#include <vulkan/vulkan.h>


class NuoVulkanDevice;


class NuoVulkanSurface : public std::enable_shared_from_this<NuoVulkanSurface>
{
    
    VkSurfaceKHR _vkSurface;
    VkSurfaceCapabilitiesKHR _vkSurfaceCapabilities;
    
    NuoVulkanSurface() = delete;
    NuoVulkanSurface(const NuoVulkanSurface& o) = delete;
    PNuoVulkanInstance _instance;
    
public:
    
    NuoVulkanSurface(const PNuoVulkanInstance& instance, void* view);
    ~NuoVulkanSurface();
    
    VkSurfaceKHR VulkanSurface() { return _vkSurface; }

};

#endif /* NuoVulkanSurface_hpp */
