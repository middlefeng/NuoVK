//
//  NuoVulkanPhysicalDevice.cpp
//  Cube-macOS
//
//  Created by middleware on 5/21/18.
//

#include "NuoVulkanPhysicalDevice.h"

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

#include "NuoVulkanDevice.h"
#include "NuoVulkanSurface.h"


struct NuoVulkanDeviceInternal
{
    VkDevice _device;
};


struct NuoVulkanSurfaceInternal
{
    VkSurfaceKHR _surface;
};


struct NuoVulkanPhysicalDeviceInternal
{
    VkPhysicalDevice _device;
};


struct NuoVulkanPhysicalDeviceProperties
{
    VkPhysicalDeviceProperties _properties;
    std::vector<VkQueueFamilyProperties> _queueFamilyProperties;
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



void NuoVulkanPhysicalDevice::CacheQueueFamilyProperties()
{
    if (!_properties || _properties->_queueFamilyProperties.size())
        return;
    
    uint32_t familyCount = QueueFamiliesCount();
    
    _properties->_queueFamilyProperties.resize(familyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(_internal->_device, &familyCount,
                                             &_properties->_queueFamilyProperties[0]);
}



void NuoVulkanPhysicalDevice::QueryExtensions()
{
    if (_extensionsDesired.size())
        return;
    
    uint32_t deviceExtensionCount;
    VkResult err = vkEnumerateDeviceExtensionProperties(_internal->_device, NULL, &deviceExtensionCount, NULL);
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
    
    return _properties->_properties.deviceName;
}



uint32_t NuoVulkanPhysicalDevice::QueueFamiliesCount()
{
    uint32_t count = 0;
    
    vkGetPhysicalDeviceQueueFamilyProperties(_internal->_device, &count, nullptr);
    return count;
}


bool NuoVulkanPhysicalDevice::QueueFamilySupportGraphics(uint32_t index)
{
    CacheQueueFamilyProperties();
    
    const VkQueueFamilyProperties& props = _properties->_queueFamilyProperties[index];
    return props.queueFlags | VK_QUEUE_GRAPHICS_BIT;
}


bool NuoVulkanPhysicalDevice::QueueFamilySupportPresent(uint32_t index, const PNuoVulkanSurface& surface)
{
    VkBool32 presentable = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(_internal->_device, index,
                                         surface->_internal->_surface,
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
    
    float queuePriorities[1] = { 0.0 };
    VkDeviceQueueCreateInfo queues[1];
    queues[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queues[0].pNext = NULL;
    queues[0].queueFamilyIndex = queueFamilyIndex;
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
        .enabledExtensionCount = (uint32_t)_extensionsDesired.size(),
        .ppEnabledExtensionNames = &_extensionsDesired[0],
        .pEnabledFeatures = NULL,  // If specific features are required, pass them in here
    };
    
    NuoVulkanDeviceInternal* deviceInternal = new NuoVulkanDeviceInternal;
    VkResult err = vkCreateDevice(_internal->_device, &createInfo,
                                  nullptr, &deviceInternal->_device);
    assert(err == VK_SUCCESS);
    
    PNuoVulkanDevice device(new NuoVulkanDevice(deviceInternal));
    return device;
}



