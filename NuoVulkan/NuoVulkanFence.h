//
//  NuoVulkanFence.hpp
//  Cube-macOS
//
//  Created by middleware on 5/31/18.
//

#ifndef NuoVulkanFence_hpp
#define NuoVulkanFence_hpp

#include <vulkan/vulkan.h>
#include <memory>

class NuoVulkanDevice;

typedef std::shared_ptr<NuoVulkanDevice> PNuoVulkanDevice;



class NuoVulkanFence
{
    VkFence _vkFence;

public:
    
    NuoVulkanFence(const PNuoVulkanDevice& device);
    
    VkFence* VulkanFence() { return &_vkFence; }
    
};



class NuoVulkanSemaphore
{
    VkSemaphore _vkSemaphore;

public:
    
    NuoVulkanSemaphore(const PNuoVulkanDevice& device);
    
    VkSemaphore VulkanSempahore() { return _vkSemaphore; }
};

#endif /* NuoVulkanFence_hpp */
