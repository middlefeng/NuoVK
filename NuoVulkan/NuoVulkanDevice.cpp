//
//  NuoVulkanDevice.cpp
//  Cube-iOS
//
//  Created by middleware on 5/22/18.
//

#include "NuoVulkanDevice.h"

#include <string>

#include "NuoVulkanShaderModule.h"
#include "NuoVulkanDeviceQueue.h"
#include "NuoVulkanPhysicalDevice.h"
#include "NuoVulkanSwapChain.h"
#include "NuoVulkanSurface.h"



NuoVulkanDevice::NuoVulkanDevice(const PNuoVulkanPhysicalDevice& physicalDevice,
                                 const PNuoVulkanSurface& surface,
                                 uint32_t queueIndex,
                                 const std::vector<const char*>& extensions)
    : _physicalDevice(physicalDevice),
      _surface(surface),
      _queueIndex(queueIndex)
{
    float queuePriorities[1] = { 0.0 };
    VkDeviceQueueCreateInfo queues[1];
    queues[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queues[0].pNext = NULL;
    queues[0].queueFamilyIndex = queueIndex;
    queues[0].queueCount = 1;
    queues[0].pQueuePriorities = queuePriorities;
    queues[0].flags = 0;
    
    VkDeviceCreateInfo createInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext = NULL,
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = queues,
        .enabledLayerCount = 0,
        .ppEnabledLayerNames = NULL,
        .enabledExtensionCount = (uint32_t)extensions.size(),
        .ppEnabledExtensionNames = &extensions[0],
        .pEnabledFeatures = NULL,  // If specific features are required, pass them in here
    };
    
    VkResult err = vkCreateDevice(physicalDevice->VulkanPhysicalDevice(), &createInfo,
                                  nullptr, &_vkDevice);
    assert(err == VK_SUCCESS);
    
    memset(&_surfaceCapabilities, 0, sizeof(_surfaceCapabilities));
}


NuoVulkanDevice::~NuoVulkanDevice()
{
    vkDestroyDevice(_vkDevice, nullptr);
}


void NuoVulkanDevice::CacheSurfaceCapabilities()
{
    uint32_t* initialized = (uint32_t*)&_surfaceCapabilities;
    if (*initialized)
        return;
    
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_physicalDevice->VulkanPhysicalDevice(),
                                              _surface->VulkanSurface(),
                                              &_surfaceCapabilities);
}


void NuoVulkanDevice::CacheSurfaceFormatsInfo()
{
    if (_surfaceFormats.size())
        return;
    
    uint32_t supportedCount = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(_physicalDevice->VulkanPhysicalDevice(),
                                         _surface->VulkanSurface(), &supportedCount, nullptr);
    
    _surfaceFormats.resize(supportedCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(_physicalDevice->VulkanPhysicalDevice(),
                                         _surface->VulkanSurface(), &supportedCount,
                                         &_surfaceFormats[0]);
}


PNuoVulkanShaderModule NuoVulkanDevice::CreateShaderModule(const std::string& path)
{
    return std::make_shared<NuoVulkanShaderModule>(shared_from_this(), path);
}


PNuoVulkanSwapChain NuoVulkanDevice::CreateSwapChain(const PNuoVulkanSwapChain& oldChain)
{
    CacheSurfaceCapabilities();
    CacheSurfaceFormatsInfo();
    
    VkSurfaceTransformFlagBitsKHR preTransform;
    if (_surfaceCapabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
        preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    else
        preTransform = _surfaceCapabilities.currentTransform;
    
    VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    VkCompositeAlphaFlagBitsKHR compositeAlphaFlags[] =
    {
        VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
        VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
        VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
    };
    for (uint32_t i = 0; i < sizeof(compositeAlphaFlags) / sizeof(compositeAlphaFlags[0]); ++i)
    {
        if (_surfaceCapabilities.supportedCompositeAlpha & compositeAlphaFlags[i])
        {
            compositeAlpha = compositeAlphaFlags[i];
            break;
        }
    }
    
    VkSwapchainCreateInfoKHR swapChainInfo =
    {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext = nullptr,
        .surface = _surface->VulkanSurface(),
        .minImageCount = _surfaceCapabilities.maxImageCount,
        .imageFormat = _surfaceFormats[0].format,
        .imageColorSpace = _surfaceFormats[0].colorSpace,
        .imageExtent = _surfaceCapabilities.currentExtent,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .preTransform = preTransform,
        .compositeAlpha = compositeAlpha,
        .imageArrayLayers = 1,
        .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .queueFamilyIndexCount = 0,
        .pQueueFamilyIndices = NULL,
        .presentMode = VK_PRESENT_MODE_FIFO_KHR,
        .oldSwapchain = oldChain ? oldChain->VulaknSwapchain() : nullptr,
        .clipped = true,
    };
    
    return std::make_shared<NuoVulkanSwapChain>(shared_from_this(),
                                                swapChainInfo);
}



PNuoVulkanDeviceQueue NuoVulkanDevice::DeviceQueue()
{
    if (!_deviceQueue)
        _deviceQueue = std::make_shared<NuoVulkanDeviceQueue>(shared_from_this(), _queueIndex);
    
    return _deviceQueue;
}


