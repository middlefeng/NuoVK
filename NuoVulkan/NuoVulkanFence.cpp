//
//  NuoVulkanFence.cpp
//  Cube-macOS
//
//  Created by middleware on 5/31/18.
//

#include "NuoVulkanFence.h"
#include "NuoVulkanDevice.h"


NuoVulkanFence::NuoVulkanFence(const PNuoVulkanDevice& device)
{
    VkFenceCreateInfo fenceCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
        .pNext = NULL,
        .flags = VK_FENCE_CREATE_SIGNALED_BIT
    };
    
    VkResult err = vkCreateFence(device->VulkanDevice(), &fenceCreateInfo, nullptr, &_vkFence);
    assert(err == VK_SUCCESS);
}



NuoVulkanSemaphore::NuoVulkanSemaphore(const PNuoVulkanDevice& device)
{
    VkSemaphoreCreateInfo semaphoreCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        .pNext = NULL,
        .flags = 0,
    };
    
    VkResult err = vkCreateSemaphore(device->VulkanDevice(), &semaphoreCreateInfo, nullptr, &_vkSemaphore);
    assert(err == VK_SUCCESS);
}
