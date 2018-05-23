//
//  NuoVulkanDevice.cpp
//  Cube-iOS
//
//  Created by middleware on 5/22/18.
//

#include "NuoVulkanDevice.h"

#include <vulkan/vulkan.h>
#include <string>

#include "NuoVulkanShaderModule.h"
#include "NuoVulkanDeviceQueue.h"


struct NuoVulkanDeviceInternal
{
    VkDevice _device;
};


struct NuoVulkanShaderModuleInternal
{
    VkShaderModule _module;
};


struct NuoVulkanDeviceQueueInternal
{
    VkQueue _queue;
};



NuoVulkanDevice::NuoVulkanDevice(const PNuoVulkanPhysicalDevice& physicalDevice,
                                 uint32_t queueIndex,
                                 NuoVulkanDeviceInternal* internal)
    : _internal(internal),
      _physicalDevice(physicalDevice),
      _queueIndex(queueIndex)
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


PNuoVulkanShaderModule NuoVulkanDevice::CreateShaderModule(const std::string& path)
{
    FILE* file = fopen(path.c_str(), "r");
    if (file)
    {
        NuoVulkanShaderModuleInternal* shaderModuleIntrenal = new NuoVulkanShaderModuleInternal;
        
        int error = fseek(file, 0, SEEK_END);
        assert(!error);
        
        size_t pos = ftell(file);
        uint8_t* pCode = new uint8_t[pos];
        
        rewind(file);
        fread((void*)pCode, pos, 1, file);
        fclose(file);
        
        VkShaderModuleCreateInfo shaderInfo =
        {
            .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .codeSize = pos,
            .pCode = (const uint32_t*)pCode
        };
        
        VkResult err = vkCreateShaderModule(_internal->_device, &shaderInfo, NULL, &shaderModuleIntrenal->_module);
        assert(err == VK_SUCCESS);
        
        PNuoVulkanShaderModule module(new NuoVulkanShaderModule(shared_from_this(),
                                                                pCode, pos, shaderModuleIntrenal));
        return module;
    }
    
    return nullptr;
}


void NuoVulkanDevice::DestroyShaderModule(const PNuoVulkanShaderModule& shaderModule)
{
    vkDestroyShaderModule(_internal->_device,
                          shaderModule->_internal->_module,
                          nullptr);
}



PNuoVulkanDeviceQueue NuoVulkanDevice::DeviceQueue()
{
    NuoVulkanDeviceQueueInternal* deviceQueueInternal = new NuoVulkanDeviceQueueInternal;
    vkGetDeviceQueue(_internal->_device, _queueIndex, 0, &deviceQueueInternal->_queue);
    
    PNuoVulkanDeviceQueue queue(new NuoVulkanDeviceQueue(deviceQueueInternal));
    return queue;
}


