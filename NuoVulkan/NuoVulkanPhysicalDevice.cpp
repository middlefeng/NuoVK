//
//  NuoVulkanPhysicalDevice.cpp
//  Cube-macOS
//
//  Created by middleware on 5/21/18.
//

#include "NuoVulkanPhysicalDevice.h"
#include <vulkan/vulkan.h>


struct NuoVulkanPhysicalDeviceInternal
{
    VkPhysicalDevice _device;
};


struct NuoVulkanPhysicalDeviceProperties
{
    VkPhysicalDeviceProperties _properties;
};



NuoVulkanPhysicalDevice::NuoVulkanPhysicalDevice(const std::shared_ptr<NuoVulkanInstance>& instance,
                                                 NuoVulkanPhysicalDeviceInternal* internal)
    : _instance(instance),
      _internal(internal),
      _properties(nullptr)
{
    assert(_internal);
}


NuoVulkanPhysicalDevice::~NuoVulkanPhysicalDevice()
{
    if (_properties)
        delete _properties;
    
    if (_internal)
        delete _internal;
}



void NuoVulkanPhysicalDevice::CacheProperties()
{
    if (!_properties)
    {
        _properties = new NuoVulkanPhysicalDeviceProperties;
        vkGetPhysicalDeviceProperties(_internal->_device, &_properties->_properties);
    }
}



const char* NuoVulkanPhysicalDevice::Name()
{
    CacheProperties();
    
    return _properties->_properties.deviceName;
}



uint32_t NuoVulkanPhysicalDevice::QueueFamiliesCount()
{
    uint32_t count = 0;
    
    vkGetPhysicalDeviceQueueFamilyProperties(_internal->_device, &count, nullptr);
    return count;
}



