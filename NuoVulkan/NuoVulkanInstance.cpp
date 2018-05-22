//
//  NuoVulkanInstance.cpp
//  Cube-macOS
//
//  Created by middleware on 5/21/18.
//

#include "NuoVulkanInstance.h"

#include <vulkan/vulkan.h>
#include <vulkan/vk_sdk_platform.h>
#include <vulkan/vulkan_macos.h>



struct NuoVulkanInstanceInternal
{
    VkInstance _inst;
};



NuoVulkanInstance::NuoVulkanInstance(const std::string& name)
    : _name(name)
{
    _internal = new NuoVulkanInstanceInternal;
}


NuoVulkanInstance::~NuoVulkanInstance()
{
    delete _internal;
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
    
    err = vkCreateInstance(&instInfo, NULL, &_internal->_inst);
    assert(err == VK_SUCCESS);
        
    delete[] extensions;
}

