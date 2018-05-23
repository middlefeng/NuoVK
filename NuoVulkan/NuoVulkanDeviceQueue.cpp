//
//  NuoVulkanDeviceQueue.cpp
//  Cube-iOS
//
//  Created by middleware on 5/22/18.
//

#include "NuoVulkanDeviceQueue.h"

#include <vulkan/vulkan.h>

struct NuoVulkanDeviceQueueInternal
{
    VkQueue _queue;
};



NuoVulkanDeviceQueue::NuoVulkanDeviceQueue(NuoVulkanDeviceQueueInternal* internal)
    : _internal(internal)
{
}


NuoVulkanDeviceQueue::~NuoVulkanDeviceQueue()
{
    if (_internal)
        delete _internal;
}
