//
//  NuoVulkanShaderModule.cpp
//  Cube-iOS
//
//  Created by middleware on 5/22/18.
//

#include "NuoVulkanShaderModule.h"

#include <stdio.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

#include "NuoVulkanDevice.h"



struct NuoVulkanShaderModuleInternal
{
    VkShaderModule _module;
};


NuoVulkanShaderModule::NuoVulkanShaderModule(const PNuoVulkanDevice& device,
                                             uint8_t* pCode, size_t pCodeSize,
                                             NuoVulkanShaderModuleInternal* internal)
    : _internal(internal),
      _pCode(pCode),
      _pCodeSize(pCodeSize),
      _device(device)
{
}



NuoVulkanShaderModule::~NuoVulkanShaderModule()
{
    if (_pCode)
        delete[] _pCode;
    
    if (_internal)
    {
        _device->DestroyShaderModule(shared_from_this());
        delete _internal;
    }
}
