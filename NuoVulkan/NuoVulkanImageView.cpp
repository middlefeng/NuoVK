//
//  NuoVulkanImageView.cpp
//  Cube-macOS
//
//  Created by middleware on 5/23/18.
//

#include "NuoVulkanImageView.h"
#include "NuoVulkanDevice.h"


NuoVulkanImageView::NuoVulkanImageView(const PNuoVulkanDevice& device,
                                       const VkImageViewCreateInfo& createInfo)
    : _device(device)
{
    VkResult err = vkCreateImageView(device->VulkanDevice(), &createInfo, nullptr, &_vkImageView);
    assert(err == VK_SUCCESS);
}


NuoVulkanImageView::~NuoVulkanImageView()
{
    vkDestroyImageView(_device->VulkanDevice(), _vkImageView, nullptr);
}
