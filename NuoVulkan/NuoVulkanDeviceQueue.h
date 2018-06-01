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
class NuoVulkanCommandBuffer;

typedef std::shared_ptr<NuoVulkanDevice> PNuoVulkanDevice;
typedef std::shared_ptr<NuoVulkanCommandBuffer> PNuoVulkanCommandBuffer;


class NuoVulkanDeviceQueue : public std::enable_shared_from_this<NuoVulkanDeviceQueue>
{
    
    VkQueue _vkQueue;
    VkCommandPool _vkCommandPool;
    uint32_t _vkQueueFamilyIndex;
    
    PNuoVulkanDevice _device;

    NuoVulkanDeviceQueue() = delete;
    
    void CacheCommandPool();
    
public:
    
    NuoVulkanDeviceQueue(const PNuoVulkanDevice& device,
                         uint32_t queueFamilyIndex);
    ~NuoVulkanDeviceQueue();
    
    VkQueue VulkanQueue() { return _vkQueue; }
    VkCommandPool VulkanCommandPool();
    
    PNuoVulkanCommandBuffer CommandBuffer();
    const PNuoVulkanDevice& Device();
};

#endif /* NuoVulkanDeviceQueue_hpp */
