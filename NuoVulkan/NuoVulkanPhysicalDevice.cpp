//
//  NuoVulkanPhysicalDevice.cpp
//  Cube-macOS
//
//  Created by middleware on 5/21/18.
//

#include "NuoVulkanPhysicalDevice.h"

#include "NuoVulkanDevice.h"
#include "NuoVulkanSurface.h"

#include <vulkan/vulkan_core.h>



NuoVulkanPhysicalDevice::NuoVulkanPhysicalDevice(const std::shared_ptr<NuoVulkanInstance>& instance,
                                                 VkPhysicalDevice vkPhysicalDevice)
    : _instance(instance),
      _vkPhysicalDevice(vkPhysicalDevice)
{
    memset(&_properties, 0, sizeof(_properties));
}


NuoVulkanPhysicalDevice::~NuoVulkanPhysicalDevice()
{
}



void NuoVulkanPhysicalDevice::CacheProperties()
{
    uint32_t* initialized = (uint32_t*)&_properties;
    if (!(*initialized))
        vkGetPhysicalDeviceProperties(_vkPhysicalDevice, &_properties);
}



void NuoVulkanPhysicalDevice::CacheQueueFamilyProperties()
{
    if (_queueFamilyProperties.size())
        return;
    
    uint32_t familyCount = QueueFamiliesCount();
    
    _queueFamilyProperties.resize(familyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(_vkPhysicalDevice, &familyCount,
                                             &_queueFamilyProperties[0]);
}



void NuoVulkanPhysicalDevice::QueryExtensions()
{
    if (_extensionsDesired.size())
        return;
    
    uint32_t deviceExtensionCount;
    VkResult err = vkEnumerateDeviceExtensionProperties(_vkPhysicalDevice, NULL, &deviceExtensionCount, NULL);
    assert(err == VK_SUCCESS);
    
    VkExtensionProperties* extensions = new VkExtensionProperties[deviceExtensionCount];
    
    for (uint32_t i = 0; i < deviceExtensionCount; ++i)
    {
        VkExtensionProperties* extension = extensions + i;
        _extensions.push_back(extensions->extensionName);
    }
    
    for (const std::string& extName : _extensions)
    {
        if (!strcmp(VK_KHR_SWAPCHAIN_EXTENSION_NAME, extName.c_str()))
            _extensionsDesired.push_back(extName.c_str());
    }
    
    delete[] extensions;
}



const char* NuoVulkanPhysicalDevice::Name()
{
    CacheProperties();
    
    return _properties.deviceName;
}



uint32_t NuoVulkanPhysicalDevice::QueueFamiliesCount()
{
    uint32_t count = 0;
    
    vkGetPhysicalDeviceQueueFamilyProperties(_vkPhysicalDevice, &count, nullptr);
    return count;
}


bool NuoVulkanPhysicalDevice::QueueFamilySupportGraphics(uint32_t index)
{
    CacheQueueFamilyProperties();
    
    const VkQueueFamilyProperties& props = _queueFamilyProperties[index];
    return props.queueFlags | VK_QUEUE_GRAPHICS_BIT;
}


bool NuoVulkanPhysicalDevice::QueueFamilySupportPresent(uint32_t index, const PNuoVulkanSurface& surface)
{
    VkBool32 presentable = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(_vkPhysicalDevice, index,
                                         surface->VulkanSurface(),
                                         &presentable);
    
    return presentable;
}


PNuoVulkanDevice NuoVulkanPhysicalDevice::CreateDevice(const PNuoVulkanSurface& surface)
{
    QueryExtensions();
    
    uint32_t queueFamilyCount = QueueFamiliesCount();
    uint32_t queueFamilyIndex = 0xFFFFFFFF;
    for (uint32_t i = 0; i < queueFamilyCount; ++i)
    {
        if (QueueFamilySupportGraphics(i) && QueueFamilySupportPresent(i, surface))
        {
            queueFamilyIndex = i;
            break;
        }
    }
    
    assert(queueFamilyIndex < 0xFFFF);
    
    PNuoVulkanDevice device(new NuoVulkanDevice(shared_from_this(),
                                                surface,
                                                queueFamilyIndex,
                                                _extensionsDesired));
    return device;
}



