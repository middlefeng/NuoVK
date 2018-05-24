//
//  NuoVulkanInstance.cpp
//  Cube-macOS
//
//  Created by middleware on 5/21/18.
//

#include "NuoVulkanInstance.h"

#include "NuoVulkanSurface.h"
#include "NuoVulkanPhysicalDevice.h"

#include <vulkan/vk_sdk_platform.h>
#include <vulkan/vulkan_macos.h>



NuoVulkanInstance::NuoVulkanInstance(const std::string& name)
    : _name(name), _vkInstance(0)
{
}


NuoVulkanInstance::~NuoVulkanInstance()
{
    if (!_vkInstance)
        return;
    
    vkDestroyInstance(_vkInstance, nullptr);
}



void NuoVulkanInstance::Initialize()
{
    uint32_t extensionCount = 0;
    VkResult err = vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    assert(err == VK_SUCCESS);
    
    VkExtensionProperties* extensions = nullptr;
    if (extensionCount > 0)
    {
        extensions = new VkExtensionProperties[extensionCount];
        err = vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, extensions);
        assert(err == VK_SUCCESS);
    }
    
    for (uint32_t i = 0; i < extensionCount; ++i)
    {
        VkExtensionProperties* extension = extensions + i;
        if (!strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extension->extensionName))
            _extensions.push_back(extension->extensionName);
        if (!strcmp(VK_MVK_MACOS_SURFACE_EXTENSION_NAME, extension->extensionName))
            _extensions.push_back(extension->extensionName);
    }
    
    for (const std::string& name : _extensions)
        _extensionsDesired.push_back(name.c_str());
    
    const VkApplicationInfo app =
    {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pNext = NULL,
        .pApplicationName = _name.c_str(),
        .applicationVersion = 0,
        .pEngineName = _name.c_str(),
        .engineVersion = 0,
        .apiVersion = VK_API_VERSION_1_0,
    };
    
    VkInstanceCreateInfo instInfo =
    {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pNext = NULL,
        .pApplicationInfo = &app,
        .enabledLayerCount = 0,
        .ppEnabledLayerNames = nullptr,
        .enabledExtensionCount = (uint32_t)_extensionsDesired.size(),
        .ppEnabledExtensionNames = (const char *const *)&_extensionsDesired[0],
    };
    
    err = vkCreateInstance(&instInfo, NULL, &_vkInstance);
    assert(err == VK_SUCCESS);
        
    delete[] extensions;
}


NuoVulkanPhysicalDeviceList NuoVulkanInstance::PhysicalDevices()
{
    uint32_t gpuCount = 0;
    VkResult err = vkEnumeratePhysicalDevices(_vkInstance, &gpuCount, NULL);
    assert(err == VK_SUCCESS && gpuCount > 0);
    
    VkPhysicalDevice* physicalDevices = new VkPhysicalDevice[gpuCount];
    err = vkEnumeratePhysicalDevices(_vkInstance, &gpuCount, physicalDevices);
    assert(err == VK_SUCCESS);
    
    NuoVulkanPhysicalDeviceList devices;
    
    for (uint32_t i = 0; i < gpuCount; ++i)
    {
        VkPhysicalDevice* physicalDevice = physicalDevices + i;
        PNuoVulkanPhysicalDevice device(new NuoVulkanPhysicalDevice(shared_from_this(),
                                                                    *physicalDevice));
        devices.push_back(device);
    }
    
    delete[] physicalDevices;
    
    return devices;
}



PNuoVulkanSurface NuoVulkanInstance::MakeSurface(void* view)
{
    PNuoVulkanSurface vulkanSurface(new NuoVulkanSurface(shared_from_this(), view));
    
    return vulkanSurface;
}


