//
//  NuoVulkanSurface.cpp
//  Cube-macOS
//
//  Created by middleware on 5/22/18.
//

#include "NuoVulkanSurface.h"


#include <vulkan/vulkan_macos.h>




NuoVulkanSurface::NuoVulkanSurface(const PNuoVulkanInstance& instance, void* view)
    : _instance(instance)
{
    VkMacOSSurfaceCreateInfoMVK surface;
    surface.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
    surface.pNext = NULL;
    surface.flags = 0;
    surface.pView = view;
    
    VkResult err = vkCreateMacOSSurfaceMVK(instance->VulkanInstance(), &surface, NULL, &_vkSurface);
    assert(err == VK_SUCCESS);
    
    memset(&_vkSurfaceCapabilities, 0, sizeof(_vkSurfaceCapabilities));
}


NuoVulkanSurface::~NuoVulkanSurface()
{
    vkDestroySurfaceKHR(_instance->VulkanInstance(), _vkSurface, nullptr);
}

