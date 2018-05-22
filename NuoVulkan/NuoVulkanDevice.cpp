//
//  NuoVulkanDevice.cpp
//  Cube-iOS
//
//  Created by middleware on 5/22/18.
//

#include "NuoVulkanDevice.h"

#include <vulkan/vulkan.h>
#include <string>


struct NuoVulkanDeviceInternal
{
    VkDevice _device;
};



NuoVulkanDevice::NuoVulkanDevice(NuoVulkanDeviceInternal* internal)
    : _internal(internal)
{
    assert(_internal != nullptr);
}


NuoVulkanDevice::~NuoVulkanDevice()
{
    if (_internal)
    {
        vkDestroyDevice(_internal->_device, nullptr);
        delete _internal;
    }
}
