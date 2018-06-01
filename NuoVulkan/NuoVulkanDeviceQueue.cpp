//
//  NuoVulkanDeviceQueue.cpp
//  Cube-iOS
//
//  Created by middleware on 5/22/18.
//

#include "NuoVulkanDeviceQueue.h"

#include "NuoVulkanDevice.h"
#include "NuoVulkanCommandBuffer.h"



NuoVulkanDeviceQueue::NuoVulkanDeviceQueue(const PNuoVulkanDevice& device,
                                           uint32_t queueFamilyIndex)
    : _device(device),
      _vkQueueFamilyIndex(queueFamilyIndex)
{
    vkGetDeviceQueue(device->VulkanDevice(), queueFamilyIndex, 0, &_vkQueue);
    memset(&_vkCommandPool, 0, sizeof(_vkCommandPool));
}


NuoVulkanDeviceQueue::~NuoVulkanDeviceQueue()
{
}


void NuoVulkanDeviceQueue::CacheCommandPool()
{
    const uint32_t* initialized = (uint32_t*)&_vkCommandPool;
    
    if (*initialized)
        return;
    
    const VkCommandPoolCreateInfo cmdPoolInfo =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .pNext = NULL,
        .queueFamilyIndex = _vkQueueFamilyIndex,
        .flags = 0,
    };
    
    VkResult err = vkCreateCommandPool(_device->VulkanDevice(), &cmdPoolInfo, NULL, &_vkCommandPool);
    assert(err == VK_SUCCESS);
}


VkCommandPool NuoVulkanDeviceQueue::VulkanCommandPool()
{
    CacheCommandPool();
    return _vkCommandPool;
}


const PNuoVulkanDevice& NuoVulkanDeviceQueue::Device()
{
    return _device;
}


PNuoVulkanCommandBuffer NuoVulkanDeviceQueue::CommandBuffer()
{
    return std::make_shared<NuoVulkanCommandBuffer>(shared_from_this());
}
