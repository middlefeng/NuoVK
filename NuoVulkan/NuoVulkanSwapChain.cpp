//
//  NuoVulkanSwapChain.cpp
//  Cube-macOS
//
//  Created by middleware on 5/22/18.
//

#include "NuoVulkanSwapChain.h"

#include "NuoVulkanDevice.h"
#include "NuoVulkanImageView.h"
#include "NuoVulkanFence.h"
#include "NuoVulkanDeviceQueue.h"


NuoVulkanSwapChain::NuoVulkanSwapChain(const PNuoVulkanDevice& device,
                                       const VkSwapchainCreateInfoKHR& createInfo)
    : _device(device),
      _imageCount(createInfo.minImageCount),
      _imageFormat(createInfo.imageFormat),
      _currentIndex(0)
{
    VkResult err = vkCreateSwapchainKHR(device->VulkanDevice(),
                                        &createInfo, nullptr, &_vkSwapChain);
    assert(err == VK_SUCCESS);
}


NuoVulkanSwapChain::~NuoVulkanSwapChain()
{
    vkDestroySwapchainKHR(_device->VulkanDevice(), _vkSwapChain, nullptr);
}


void NuoVulkanSwapChain::CacheSwapImages()
{
    if (_images.size())
        return;
    
    uint32_t imageCount = 0;
    vkGetSwapchainImagesKHR(_device->VulkanDevice(), _vkSwapChain, &imageCount, nullptr);
    assert(imageCount == _imageCount);
    
    _images.resize(imageCount);
    VkResult err = vkGetSwapchainImagesKHR(_device->VulkanDevice(),
                                           _vkSwapChain, &imageCount, &_images[0]);
    assert(err == VK_SUCCESS);
}


void NuoVulkanSwapChain::CreateSemaphores()
{
    for (uint32_t i = 0; i < _images.size(); ++i)
    {
        PNuoVulkanSemaphore semaphoreDrawComplete = std::make_shared<NuoVulkanSemaphore>(_device);
        PNuoVulkanSemaphore semaphoreImageAcquire = std::make_shared<NuoVulkanSemaphore>(_device);
        PNuoVulkanFence fence = std::make_shared<NuoVulkanFence>(_device);
        
        _sempaphoresDrawComplete.push_back(semaphoreDrawComplete);
        _sempaphoresImageAcquire.push_back(semaphoreImageAcquire);
        _fence.push_back(fence);
    }
}


const std::vector<PNuoVulkanImageView>& NuoVulkanSwapChain::ImageViews()
{
    CacheSwapImages();
    
    if (_imageViews.size())
        return _imageViews;
    
    for (uint32_t i = 0; i < _images.size(); ++i)
    {
        VkImageViewCreateInfo createInfo =
        {
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .pNext = NULL,
            .format = _imageFormat,
            .components =
            {
                .r = VK_COMPONENT_SWIZZLE_R,
                .g = VK_COMPONENT_SWIZZLE_G,
                .b = VK_COMPONENT_SWIZZLE_B,
                .a = VK_COMPONENT_SWIZZLE_A,
            },
            .subresourceRange =
            {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .baseMipLevel = 0,
                .levelCount = 1,
                .baseArrayLayer = 0,
                .layerCount = 1
            },
            .viewType = VK_IMAGE_VIEW_TYPE_2D,
            .flags = 0,
        };
        
        createInfo.image = _images[i];
        
        PNuoVulkanImageView imageView = std::make_shared<NuoVulkanImageView>(_device, createInfo);
        _imageViews.push_back(imageView);
    }
    
    return _imageViews;
}



const PNuoVulkanImageView& NuoVulkanSwapChain::NextDrawableIndex()
{
    vkWaitForFences(_device->VulkanDevice(), 1, _fence[_currentIndex]->VulkanFence(), VK_TRUE, UINT64_MAX);
    vkResetFences(_device->VulkanDevice(), 1, _fence[_currentIndex]->VulkanFence());
    
    VkResult err = vkAcquireNextImageKHR(_device->VulkanDevice(), _vkSwapChain, UINT64_MAX,
                                         _sempaphoresImageAcquire[_currentIndex]->VulkanSempahore(),
                                         VK_NULL_HANDLE, &_currentImageIndex);
    
    return _imageViews[_currentImageIndex];
}



void NuoVulkanSwapChain::Present(const PNuoVulkanDeviceQueue& queue)
{
    const VkSemaphore waitSempahores[] = { _sempaphoresDrawComplete[_currentIndex]->VulkanSempahore() };
    
    VkPresentInfoKHR presentInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .pNext = NULL,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = waitSempahores,
        .swapchainCount = 1,
        .pSwapchains = &_vkSwapChain,
        .pImageIndices = &_currentImageIndex,
    };
    
    VkResult err = vkQueuePresentKHR(queue->VulkanQueue(), &presentInfo);
    assert(err == VK_SUCCESS);
}


