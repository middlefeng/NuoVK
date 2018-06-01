//
//  NuoVulkanCommandBuffer.hpp
//  Cube-macOS
//
//  Created by middleware on 5/31/18.
//

#ifndef NuoVulkanCommandBuffer_hpp
#define NuoVulkanCommandBuffer_hpp


#include <vulkan/vulkan.h>
#include <memory>


class NuoVulkanDeviceQueue;
class NuoVulkanFence;
class NuoVulkanSemaphore;

typedef std::shared_ptr<NuoVulkanDeviceQueue> PNuoVulkanDeviceQueue;
typedef std::shared_ptr<NuoVulkanFence> PNuoVulkanFence;
typedef std::shared_ptr<NuoVulkanSemaphore> PNuoVulkanSemaphore;


class NuoVulkanCommandBuffer
{
    VkCommandBuffer _vkCommandBuffer;
    
    PNuoVulkanDeviceQueue _queue;

public:
    
    NuoVulkanCommandBuffer(const PNuoVulkanDeviceQueue& queue);
    
    void Begin();
    void End();
    void Commit(const PNuoVulkanSemaphore& waitSemaphore,
                const PNuoVulkanSemaphore& signalSempahore,
                const PNuoVulkanFence& fence);

};

#endif /* NuoVulkanCommandBuffer_hpp */
