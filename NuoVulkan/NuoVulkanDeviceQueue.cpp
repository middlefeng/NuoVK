//
//  NuoVulkanDeviceQueue.cpp
//  Cube-iOS
//
//  Created by middleware on 5/22/18.
//

#include "NuoVulkanDeviceQueue.h"
#include "NuoVulkanDevice.h"



NuoVulkanDeviceQueue::NuoVulkanDeviceQueue(const PNuoVulkanDevice& device,
                                           uint32_t queueFamilyIndex)
{
    vkGetDeviceQueue(device->VulkanDevice(), queueFamilyIndex, 0, &_queue);
}

NuoVulkanDeviceQueue::~NuoVulkanDeviceQueue()
{
}
