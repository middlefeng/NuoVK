//
//  NuoVulkanSwapChain.cpp
//  Cube-macOS
//
//  Created by middleware on 5/22/18.
//

#include "NuoVulkanSwapChain.h"

#include "NuoVulkanDevice.h"


NuoVulkanSwapChain::NuoVulkanSwapChain(const PNuoVulkanDevice& device,
                                       const VkSwapchainCreateInfoKHR& createInfo)
    : _device(device)
{
    VkResult err = vkCreateSwapchainKHR(device->VulkanDevice(),
                                        &createInfo, nullptr, &_swapChain);
    assert(err == VK_SUCCESS);
}


NuoVulkanSwapChain::~NuoVulkanSwapChain()
{
    vkDestroySwapchainKHR(_device->VulkanDevice(), _swapChain, nullptr);
}
