//
//  NuoVulkanCommandBuffer.cpp
//  Cube-macOS
//
//  Created by middleware on 5/31/18.
//

#include "NuoVulkanCommandBuffer.h"

#include "NuoVulkanDevice.h"
#include "NuoVulkanDeviceQueue.h"
#include "NuoVulkanFence.h"


NuoVulkanCommandBuffer::NuoVulkanCommandBuffer(const PNuoVulkanDeviceQueue& queue)
    : _queue(queue)
{
    const VkCommandBufferAllocateInfo cmdInfo =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .pNext = NULL,
        .commandPool = _queue->VulkanCommandPool(),
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = 1,
    };
    
    PNuoVulkanDevice device = _queue->Device();
    VkResult err = vkAllocateCommandBuffers(device->VulkanDevice(), &cmdInfo, &_vkCommandBuffer);
    
    assert(err == VK_SUCCESS);
}


void NuoVulkanCommandBuffer::Begin()
{
    VkCommandBufferBeginInfo cmdBegininfo =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .pNext = NULL,
        .flags = 0,
        .pInheritanceInfo = NULL,
    };
    
    VkResult err = vkBeginCommandBuffer(_vkCommandBuffer, &cmdBegininfo);
    
    assert(err == VK_SUCCESS);
}


void NuoVulkanCommandBuffer::End()
{
    VkResult err = vkEndCommandBuffer(_vkCommandBuffer);
    
    assert(err == VK_SUCCESS);
}



void NuoVulkanCommandBuffer::Commit(const PNuoVulkanSemaphore& waitSemaphore,
                                    const PNuoVulkanSemaphore& signalSempahore,
                                    const PNuoVulkanFence& fence)
{
    const VkCommandBuffer cmdBufs[] = { _vkCommandBuffer };
    const VkSemaphore waitSempahores[] = { !waitSemaphore ? NULL : waitSemaphore->VulkanSempahore() };
    const VkSemaphore signalSempahores[] = { !signalSempahore ? NULL : signalSempahore->VulkanSempahore() };
    
    VkSubmitInfo commitInfo =
    {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .pNext = NULL,
        .waitSemaphoreCount = (uint32_t)(!waitSemaphore ? 0 : 1),
        .pWaitSemaphores = !waitSemaphore ? NULL : waitSempahores,
        .pWaitDstStageMask = NULL,
        .commandBufferCount = 1,
        .pCommandBuffers = cmdBufs,
        .signalSemaphoreCount = (uint32_t)(!signalSempahore ? 0 : 1),
        .pSignalSemaphores = !signalSempahore ? NULL : signalSempahores
    };
    
    VkFence vkFence = !fence ? VK_NULL_HANDLE : *fence->VulkanFence();
    VkResult err = vkQueueSubmit(_queue->VulkanQueue(), 1, &commitInfo, vkFence);
    
    assert(err == VK_SUCCESS);
}



