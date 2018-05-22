//
//  NuoVulkanSurface.cpp
//  Cube-macOS
//
//  Created by middleware on 5/22/18.
//

#include "NuoVulkanSurface.h"


#include <vulkan/vulkan.h>
#include <vulkan/vulkan_macos.h>



struct NuoVulkanSurfaceInternal
{
    VkSurfaceKHR _surface;
};



NuoVulkanSurface::NuoVulkanSurface(const std::shared_ptr<NuoVulkanInstance>& instance,
                                   NuoVulkanSurfaceInternal* internal)
    : _internal(internal),
      _instance(instance)
{
}


NuoVulkanSurface::~NuoVulkanSurface()
{
    if (_internal)
    {
        _instance->DestroySurface(shared_from_this());
        delete _internal;
    }
}
