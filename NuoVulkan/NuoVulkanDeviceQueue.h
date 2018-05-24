//
//  NuoVulkanDeviceQueue.hpp
//  Cube-iOS
//
//  Created by middleware on 5/22/18.
//

#ifndef NuoVulkanDeviceQueue_hpp
#define NuoVulkanDeviceQueue_hpp

#include <vulkan/vulkan.h>
#include <memory>


class NuoVulkanDevice;

typedef std::shared_ptr<NuoVulkanDevice> PNuoVulkanDevice;

class NuoVulkanDeviceQueue
{
    
    VkQueue _queue;

    NuoVulkanDeviceQueue() = delete;
    
public:
    
    NuoVulkanDeviceQueue(const PNuoVulkanDevice& device,
                         uint32_t queueFamilyIndex);
    ~NuoVulkanDeviceQueue();
    
    friend NuoVulkanDevice;

};

#endif /* NuoVulkanDeviceQueue_hpp */
