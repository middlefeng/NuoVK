//
//  NuoVulkanShaderModule.cpp
//  Cube-iOS
//
//  Created by middleware on 5/22/18.
//

#include "NuoVulkanShaderModule.h"

#include <stdio.h>

#include "NuoVulkanDevice.h"



NuoVulkanShaderModule::NuoVulkanShaderModule(const PNuoVulkanDevice& device,
                                             const std::string& path)
    : _device(device)
{
    FILE* file = fopen(path.c_str(), "r");
    if (file)
    {
        int error = fseek(file, 0, SEEK_END);
        assert(!error);
        
        size_t pos = ftell(file);
        _pCode.resize(pos);
        
        rewind(file);
        fread((void*)&_pCode[0], pos, 1, file);
        fclose(file);
        
        VkShaderModuleCreateInfo shaderInfo =
        {
            .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .codeSize = pos,
            .pCode = (const uint32_t*)&_pCode[0]
        };
        
        VkResult err = vkCreateShaderModule(device->VulkanDevice(), &shaderInfo, nullptr, &_vkShaderModule);
        assert(err == VK_SUCCESS);
    }
}



NuoVulkanShaderModule::~NuoVulkanShaderModule()
{
    vkDestroyShaderModule(_device->VulkanDevice(), _vkShaderModule, nullptr);
}
