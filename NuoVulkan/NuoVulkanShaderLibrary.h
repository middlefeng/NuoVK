//
//  NuoVulkanShaderLibrary.hpp
//  Cube-iOS
//
//  Created by middleware on 5/22/18.
//

#ifndef NuoVulkanShaderLibrary_hpp
#define NuoVulkanShaderLibrary_hpp


#include <memory>
#include <map>
#include <string>

class NuoVulkanDevice;
class NuoVulkanShaderModule;

typedef std::shared_ptr<NuoVulkanDevice> PNuoVulkanDevice;
typedef std::shared_ptr<NuoVulkanShaderModule> PNuoVulkanShaderModule;


class NuoVulkanShaderLibrary
{
    typedef std::map<std::string, PNuoVulkanShaderModule> ShaderModuleMap;
    
    PNuoVulkanDevice _device;
    ShaderModuleMap _shaderMap;
    std::string _libraryPath;

public:
    
    NuoVulkanShaderLibrary(const PNuoVulkanDevice& device,
                           const std::string& libraryPath);
    
    PNuoVulkanShaderModule ShaderModule(const std::string& name);

};


typedef std::shared_ptr<NuoVulkanShaderLibrary> PNuoVulkanShaderLibrary;


#endif /* NuoVulkanShaderLibrary_hpp */
