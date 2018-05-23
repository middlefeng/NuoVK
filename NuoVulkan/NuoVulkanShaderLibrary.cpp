//
//  NuoVulkanShaderLibrary.cpp
//  Cube-iOS
//
//  Created by middleware on 5/22/18.
//

#include "NuoVulkanShaderLibrary.h"

#include "NuoVulkanDevice.h"
#include "NuoVulkanShaderModule.h"


NuoVulkanShaderLibrary::NuoVulkanShaderLibrary(const PNuoVulkanDevice& device,
                                               const std::string& libraryPath)
    : _libraryPath(libraryPath),
      _device(device)
{
}


PNuoVulkanShaderModule NuoVulkanShaderLibrary::ShaderModule(const std::string& name)
{
    auto pos = _shaderMap.find(name);
    if (pos != _shaderMap.end())
        return pos->second;
    
    std::string path = _libraryPath + "/" + name + ".spv";
    PNuoVulkanShaderModule shaderModule = _device->CreateShaderModule(path);
    
    _shaderMap.insert(std::make_pair(name, shaderModule));
    return shaderModule;
}
